#include "../Drivers/screen.h"
#include "../Drivers/keyboard.h"
#include "../libft/includes/libft.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"

int main() {
    isr_install();
    asm volatile("sti");
    init_timer(50);
    init_keyboard();
    clear_screen();
    char *str = "Test Printf";
    ft_dprintf(1,"str: %s %s %s\n",str,str,str);
    ft_dprintf(1,"num: %d\n",19);
    ft_dprintf(1,"hex: %x || %X\n",10,10);
    ft_dprintf(1,"u: %u\n",-1);
    ft_dprintf(1,"c: %c\n",'c');
    ft_dprintf(1,"p: %p\n",str);
    ft_dprintf(1,"strlen: %d\n",ft_strlen(str));

    /* Test the interrupts */
    __asm__ __volatile__("int $0");
    __asm__ __volatile__("int $1");

    return 0;
}