/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:27:26 by abouabra          #+#    #+#             */
/*   Updated: 2022/10/02 15:06:23 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
// #include "../../Memory/kmalloc.h"

// void custom_exit(int exit_code)
// {
// 	garbage_collector(NULL,1);
// 	exit(exit_code);
// }

void	garbage_collector(void *adress, int arg)
{
	// static t_list *head;
	// t_list *node;

	
	// if(arg)
	// 	ft_lstclear(&head, free);
	// else
	// {
	// 	node = ft_lstnew(adress);
	// 	ft_lstadd_back(&head, node);
	// };
	(void) adress;
	(void) arg;
}

void	*my_alloc(size_t size)
{
	void	*str;
	(void) size;
	str = NULL;
	// str = (void *) kmalloc(size);
	if (!str)
		return (0);
	// ft_memset(str, 0, size);
	// // garbage_collector(str,0);
	return (str);
}