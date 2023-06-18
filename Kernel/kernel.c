#include "../Driver/screen.h"
#include "../ft_libft/ft_dprintf.h"

int main() {
    clear_screen();
    ft_print("Hello World\n");
    ft_print("My Name is Ayman\n");
    char *str = "Test Printf";
    ft_dprintf(0,"str: %s\n",str);
    ft_dprintf(0,"num: %d\n",19);
    ft_dprintf(0,"hex: %x || %X\n",10,10);
    ft_dprintf(0,"u: %u\n",-1);
    ft_dprintf(0,"c: %c\n",'c');
    ft_dprintf(0,"p: %p\n",str);
    return 0;
}