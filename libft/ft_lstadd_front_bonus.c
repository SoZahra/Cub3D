/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:59:19 by fzayani           #+#    #+#             */
/*   Updated: 2024/05/23 13:37:25 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
void	ft_print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s -> ", (char *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}

int	main(void)
{
	t_list *list = NULL;

	// Ajout d'éléments à la liste
	t_list *node1 = ft_lstnew("salut");
	ft_lstadd_front(&list, node1);
	ft_print_list(list);

	t_list *node2 = ft_lstnew("bjr");
	ft_lstadd_front(&list, node2);
	ft_print_list(list);

	t_list *node3 = ft_lstnew("bcp");
	ft_lstadd_front(&list, node3);
	ft_print_list(list);

	// Libération de la mémoire (facultatif pour ce test simple)
	t_list *tmp;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}

	return (0);
}*/