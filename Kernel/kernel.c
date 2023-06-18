#include "../Drivers/screen.h"
#include "../libft/includes/libft.h"
#include "../cpu/isr.h"

int main() {
    isr_install();
    clear_screen();
    ft_print("Hello World\n");
    ft_print("My Name is Ayman\n");
    char *str = "Test Printf";
    ft_dprintf(0,"str: %s %s %s\n",str,str,str);
    ft_dprintf(0,"num: %d\n",19);
    ft_dprintf(0,"hex: %x || %X\n",10,10);
    ft_dprintf(0,"u: %u\n",-1);
    ft_dprintf(0,"c: %c\n",'c');
    ft_dprintf(0,"p: %p\n",str);
    ft_dprintf(0,"strlen: %d\n",ft_strlen(str));

    /* Test the interrupts */
    __asm__ __volatile__("int $0");
    // __asm__ __volatile__("int $3");
    return 0;
}