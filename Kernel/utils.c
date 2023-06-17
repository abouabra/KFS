#include "utils.h"

void	*ft_memcpy(void *dest, void *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}