/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:23:37 by fzayani           #+#    #+#             */
/*   Updated: 2024/05/23 20:00:15 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*
int	main(void)
{
	t_list *list = NULL;

	t_list *node1 = ft_lstnew("salut");
	ft_lstadd_front(&list, node1);

	t_list *node2 = ft_lstnew("bjr");
	ft_lstadd_front(&list, node2);

	printf("%d\n", ft_lstsize(list));
}*/