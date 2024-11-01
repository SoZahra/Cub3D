/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:31:50 by fzayani           #+#    #+#             */
/*   Updated: 2024/05/23 13:35:17 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
/*
int	main(void)
{
	t_list *list = NULL;

	t_list *noeud = ft_lstnew("bjr");
	ft_lstadd_front(&list, noeud);

	t_list *noeud2 = ft_lstnew("slt");
	ft_lstadd_front(&list, noeud2);

	t_list *last = ft_lstlast(list);

	printf("%s\n", (char *)last->content);

}*/