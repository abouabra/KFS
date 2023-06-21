#ifndef SCREEN_H
#define SCREEN_H


# define VIDEO_ADDRESS 0xb8000
# define MAX_ROWS 25
# define MAX_COLS 80

// Screen device I / O ports
# define REG_SCREEN_CTRL 0x3d4
# define REG_SCREEN_DATA 0x3d5

// Attribute byte for our default colour scheme .
# define WHITE_ON_BLACK 0x0f
# define RED_ON_BLUE 0x14
# define YELLOW_ON_BLACK 0x0E
# define BLUE_ON_RED 0x41

# define DEFAULT_CLEAR_SCREEN RED_ON_BLUE
# define DEFAULT_PRINT_SCREEN YELLOW_ON_BLACK
# define DEFAULT_PRINT_ERROR BLUE_ON_RED

    // 0x0 - Black
    // 0x1 - Blue
    // 0x2 - Green
    // 0x3 - Cyan
    // 0x4 - Red
    // 0x5 - Magenta
    // 0x6 - Brown
    // 0x7 - Light gray
    // 0x8 - Dark gray
    // 0x9 - Light blue
    // 0xA - Light green
    // 0xB - Light cyan
    // 0xC - Light red
    // 0xD - Light magenta
    // 0xE - Yellow
    // 0xF - White

void print_at(char *message, int col, int row, char attr);
void print(char attr, char *message);
void ft_write(char attr, char c);
void clear_screen();
void print_backspace();

#endif