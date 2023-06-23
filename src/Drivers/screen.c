#include "../Includes/screen.h"
// Updates the hardware cursor.

// The VGA framebuffer starts at 0xB8000.
static u16int *video_memory = (u16int *)VIDEO_ADDRESS;
// Stores the cursor position.
static u8int cursor_x = 0;
static u8int cursor_y = 0;

static void move_cursor()
{
	// The screen is 80 characters wide...
	u16int cursorLocation = cursor_y * MAX_COLS + cursor_x;
	outb(REG_SCREEN_CTRL, 14);                  // Tell the VGA board we are setting the high cursor byte.
	outb(REG_SCREEN_DATA, cursorLocation >> 8); // Send the high cursor byte.
	outb(REG_SCREEN_CTRL, 15);                  // Tell the VGA board we are setting the low cursor byte.
	outb(REG_SCREEN_DATA, cursorLocation);      // Send the low cursor byte.
}

// Scrolls the text on the screen up by one line.
static void scroll()
{
	// Row 25 is the end, this means we need to scroll up
	if(cursor_y >= MAX_ROWS)
	{
		// Move the current text chunk that makes up the screen
		// back in the buffer by a line
		for (int i = 0*MAX_COLS; i < 24*MAX_COLS; i++)
			video_memory[i] = video_memory[i+MAX_COLS];

		// The last line should now be blank. Do this by writing
		// 80 spaces to it.
		for (int i = 24*MAX_COLS; i < MAX_ROWS*MAX_COLS; i+=2)
			video_memory[i] = DEFAULT_CLEAR_SCREEN;
		// The cursor should now be on the last line.
		cursor_y = 24;
	}
} 

void ft_putchar(char c)
{
	// The attribute byte is made up of two nibbles - the lower being the
	// foreground colour, and the upper the background colour.
	u16int *location;

	// Handle a backspace, by moving the cursor back one space
	if (c == 0x08 && cursor_x)
		cursor_x--;

	// Handle a tab by increasing the cursor's X, but only to a point
	// where it is divisible by 8.
	else if (c == 0x09)
		cursor_x = (cursor_x+8) & ~(8-1);

	// Handle carriage return
	else if (c == '\r')
		cursor_x = 0;

	// Handle newline by moving cursor back to left and increasing the row
	else if (c == '\n')
	{
		cursor_x = 0;
		cursor_y++;
	}
	// Handle any other printable character.
	else if(c >= ' ')
	{
		location = video_memory + (cursor_y*MAX_COLS + cursor_x);
		*location = c | (DEFAULT_PRINT_SCREEN << 8);
		cursor_x++;
	}

	// Check if we need to insert a new line because we have reached the end
	// of the screen.
	if (cursor_x >= MAX_COLS)
	{
		cursor_x = 0;
		cursor_y ++;
	}

	// Scroll the screen if needed.
	scroll();
	// Move the hardware cursor.
	move_cursor();
}

void screen_clear()
{
	// Make an attribute byte for the default colours
	u16int blank = ' ' | (DEFAULT_CLEAR_SCREEN << 8);

	for (int i = 0; i < MAX_COLS*MAX_ROWS; i++)
		video_memory[i] = blank;

	// Move the hardware cursor back to the start.
	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
} 

void ft_putstr(char *c)
{
	int i = -1;
	while (c[++i])
		ft_putchar(c[i]);
} 
