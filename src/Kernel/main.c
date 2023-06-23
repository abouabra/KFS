#include "../Includes/screen.h"
#include "../libft/includes/libft.h"

// int main(struct multiboot *mboot_ptr)
int main(void)
{
	screen_clear();
	// ft_putstr("Hello, world!\nHow are you ?"); 
	ft_dprintf(1, "Hello %d\n", ft_strlen("World"));
	return 0;
}