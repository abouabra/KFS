#include "screen.h"
#include "ports.h"
#include "../libft/includes/libft.h"

/* Declaration of private functions */
int get_cursor_offset();
void set_cursor_offset(int offset);
int put_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);
int handle_scrolling(int cursor_offset);

/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

/**
 * Print a message on the specified location
 * If col, row, are negative, we will use the current offset
 */
void print_at(char *message, int col, int row) {
    /* Set cursor if col/row are negative */
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    /* Loop through message and print it */
    int i = 0;
    while (message[i] != 0) {
        offset = put_char(message[i++], col, row, DEFAULT_PRINT_SCREEN);
        /* Compute row/col for next iteration */
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void ft_write(char c)
{
    char arr[2];
	arr[0] = c;
	arr[1] = 0;
    print_at(arr, -1, -1);
}

void ft_print(char *message)
{
    print_at(message, -1, -1);
}


/**********************************************************
 * Private kernel functions                               *
 **********************************************************/


/**
 * Innermost print function for our kernel, directly accesses the video memory 
 *
 * If 'col' and 'row' are negative, we will print at current cursor location
 * If 'attr' is zero it will use 'white on black' as default
 * Returns the offset of the next character
 * Sets the video cursor to the returned offset
 */
int put_char(char c, int col, int row, char attr) {
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    /* Error control: print a red 'E' if the coords aren't right */
    if (col >= MAX_COLS || row >= MAX_ROWS) {
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_BLUE;
        return get_offset(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();

    if (c == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    } else {
        vidmem[offset] = c;
        vidmem[offset+1] = attr;
        offset += 2;
    }

    offset = handle_scrolling(offset);
    
    set_cursor_offset(offset);
    return offset;
}

int get_cursor_offset() {
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; /* Position * size of character cell */
}

void set_cursor_offset(int offset) {
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    char *screen = (char *)VIDEO_ADDRESS;

    for (i = 0; i < screen_size; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = DEFAULT_CLEAR_SCREEN;
    }
    set_cursor_offset(get_offset(0, 0));
}


int get_offset(int col, int row)
{
    return 2 * (row * MAX_COLS + col);

}
int get_offset_row(int offset)
{
    return offset / (2 * MAX_COLS);
}
int get_offset_col(int offset)
{
    return (offset - (get_offset_row(offset)*2*MAX_COLS))/2;
}

int handle_scrolling(int cursor_offset)
{
    // If the cursor is within the screen , return it unmodified .
    if ( cursor_offset < MAX_ROWS * MAX_COLS *2)
        return cursor_offset ;

    /* Shuffle the rows back one . */
    for (int i = 1; i < MAX_ROWS; i ++) {
        ft_memcpy((get_offset(0,i) + (char *)VIDEO_ADDRESS),
            (get_offset(0,i-1) + (char *)VIDEO_ADDRESS),
            MAX_COLS *2
        );
    }

    /* Blank the last line by setting all bytes to 0 */
    char *last_line =  (char *) (get_offset(0, MAX_ROWS - 1) + ( char *)VIDEO_ADDRESS);
    
    for (int i =0; i < MAX_COLS *2; i ++) {
        last_line [i] = 0;
    }

    // Move the offset back one row , such that it is now on the last
    // row , rather than off the edge of the screen .
    cursor_offset -= 2* MAX_COLS ;
    // Return the updated cursor position .
    return cursor_offset ;
}