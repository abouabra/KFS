#include "keyboard.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "../libft/includes/libft.h"
#include "../Kernel/kernel.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define SC_MAX 57


void print_letter(u8 scancode);
void append_char(char s[], char n);
void remove_char(char s[]);

static void keyboard_callback(registers_t regs)
{
    static char key_buffer[1024];

    const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
    const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

    (void) regs;
    (void) sc_name;
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = port_byte_in(0x60);

    if (scancode > SC_MAX)
        return;
    if (scancode == BACKSPACE) {
        remove_char(key_buffer);
        print_backspace();
    }
    else if (scancode == ENTER) {
        ft_dprintf(1, "\n");
        user_input(key_buffer); /* kernel-controlled function */
        key_buffer[0] = '\0';
        // bzero 
    }
    else {
        char letter = sc_ascii[(int)scancode];
        /* Remember that kprint only accepts char[] */
        char str[2] = {letter, '\0'};
        append_char(key_buffer, letter);
        ft_dprintf(1, str);
    }
}

// void print_letter(u8 scancode) {
//     static u8 shift;
    
//     if (scancode == 0x2A || scancode == 0x36)
//     {
//         shift = 1;
//         return;
//     }
//     else if (scancode == 0x2A + 0x80 || scancode == 0x36 + 0x80)
//     {
//         shift = 0;
//         return;
//     }
//     switch (scancode) {
//         case 0x0:
//             ft_dprintf(1, "ERROR");
//             break;
//         case 0x1:
//             ft_dprintf(1, "ESC");
//             break;
//         case 0x2:
//             ft_dprintf(1, "1");
//             break;
//         case 0x3:
//             ft_dprintf(1, "2");
//             break;
//         case 0x4:
//             ft_dprintf(1, "3");
//             break;
//         case 0x5:
//             ft_dprintf(1, "4");
//             break;
//         case 0x6:
//             ft_dprintf(1, "5");
//             break;
//         case 0x7:
//             ft_dprintf(1, "6");
//             break;
//         case 0x8:
//             ft_dprintf(1, "7");
//             break;
//         case 0x9:
//             ft_dprintf(1, "8");
//             break;
//         case 0x0A:
//             ft_dprintf(1, "9");
//             break;
//         case 0x0B:
//             ft_dprintf(1, "0");
//             break;
//         case 0x0C:
//             ft_dprintf(1, "-");
//             break;
//         case 0x0D:
//             ft_dprintf(1, "+");
//             break;
//         case 0x0E:
//             ft_dprintf(1, "Backspace");
//             break;
//         case 0x0F:
//             ft_dprintf(1, "Tab");
//             break;
//         case 0x10:
//             if(shift)
//                 ft_dprintf(1, "Q");
//             else
//                 ft_dprintf(1, "q");
//             break;
//         case 0x11:
//             if(shift)
//                 ft_dprintf(1, "W");
//             else
//                 ft_dprintf(1, "w");
//             break;
//         case 0x12:
//             ft_dprintf(1, "E");
//             break;
//         case 0x13:
//             ft_dprintf(1, "R");
//             break;
//         case 0x14:
//             ft_dprintf(1, "T");
//             break;
//         case 0x15:
//             ft_dprintf(1, "Y");
//             break;
//         case 0x16:
//             ft_dprintf(1, "U");
//             break;
//         case 0x17:
//             ft_dprintf(1, "I");
//             break;
//         case 0x18:
//             ft_dprintf(1, "O");
//             break;
//         case 0x19:
//             ft_dprintf(1, "P");
//             break;
// 		case 0x1A:
// 			ft_dprintf(1, "[");
// 			break;
// 		case 0x1B:
// 			ft_dprintf(1, "]");
// 			break;
// 		case 0x1C:
// 			ft_dprintf(1, "ENTER");
// 			break;
// 		case 0x1D:
// 			ft_dprintf(1, "LCtrl");
// 			break;
// 		case 0x1E:
// 			ft_dprintf(1, "A");
// 			break;
// 		case 0x1F:
// 			ft_dprintf(1, "S");
// 			break;
//         case 0x20:
//             ft_dprintf(1, "D");
//             break;
//         case 0x21:
//             ft_dprintf(1, "F");
//             break;
//         case 0x22:
//             ft_dprintf(1, "G");
//             break;
//         case 0x23:
//             ft_dprintf(1, "H");
//             break;
//         case 0x24:
//             ft_dprintf(1, "J");
//             break;
//         case 0x25:
//             ft_dprintf(1, "K");
//             break;
//         case 0x26:
//             ft_dprintf(1, "L");
//             break;
//         case 0x27:
//             ft_dprintf(1, ";");
//             break;
//         case 0x28:
//             ft_dprintf(1, "'");
//             break;
//         case 0x29:
//             ft_dprintf(1, "`");
//             break;
// 		case 0x2A:
// 			ft_dprintf(1, "LShift");
// 			break;
// 		case 0x2B:
// 			ft_dprintf(1, "\\");
// 			break;
// 		case 0x2C:
// 			ft_dprintf(1, "Z");
// 			break;
// 		case 0x2D:
// 			ft_dprintf(1, "X");
// 			break;
// 		case 0x2E:
// 			ft_dprintf(1, "C");
// 			break;
// 		case 0x2F:
// 			ft_dprintf(1, "V");
// 			break;
//         case 0x30:
//             ft_dprintf(1, "B");
//             break;
//         case 0x31:
//             ft_dprintf(1, "N");
//             break;
//         case 0x32:
//             ft_dprintf(1, "M");
//             break;
//         case 0x33:
//             ft_dprintf(1, ",");
//             break;
//         case 0x34:
//             ft_dprintf(1, ".");
//             break;
//         case 0x35:
//             ft_dprintf(1, "/");
//             break;
//         case 0x36:
//             ft_dprintf(1, "Rshift");
//             break;
//         case 0x37:
//             ft_dprintf(1, "Keypad *");
//             break;
//         case 0x38:
//             ft_dprintf(1, "LAlt");
//             break;
//         case 0x39:
//             ft_dprintf(1, "Spc");
//             break;
//         default:
//             /* 'keuyp' event corresponds to the 'keydown' + 0x80 
//              * it may still be a scancode we haven't implemented yet, or
//              * maybe a control/escape sequence */
//             if (scancode <= 0x7f) {
//                 ft_dprintf(1, "Unknown key down");
//             }
//             break;
//     }
// }

void init_keyboard()
{
   register_interrupt_handler(IRQ1, keyboard_callback); 
}

void append_char(char s[], char n)
{
    int len = ft_strlen(s);
    s[len] = n;
    s[len +1 ] = '\0';
}

void remove_char(char s[])
{
    int len = ft_strlen(s);
    s[len-1] = '\0';
}