#include "../Drivers/screen.h"
#include "../Drivers/keyboard.h"
#include "../libft/includes/libft.h"
#include "../CPU/isr.h"
#include "../CPU/timer.h"
#include "../Memory/paging.h"
#include "kernel.h"

int main() {
    isr_install();
    irq_install();
    // Nullify all the interrupt handlers.
    // memset(&interrupt_handlers, 0, sizeof(isr_t)*256);
    initialise_paging();
    clear_screen();

    ft_dprintf(1, "Welcome To mini OS\n"
        "Enteract with shell\n"
        "Have Fun\n");
    ft_dprintf(1, "%s",PS1);

    // monitor_write("Hello, paging world!\n");
    // u32int *ptr = (u32int*)0xA0000000;
    // u32int do_page_fault = *ptr;
    return 0;
}

void user_input(char *input)
{
    if(input[0])
        ft_dprintf(1, "You entered: %s\n",input);
    if(!ft_strncmp("clear",input,-1))
        clear_screen();
    else if(!ft_strncmp("exit",input,-1))
    {
        asm volatile("hlt");
    }
    ft_dprintf(1, "%s",PS1);
}