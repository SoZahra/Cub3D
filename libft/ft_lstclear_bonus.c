/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:27:15 by fzayani           #+#    #+#             */
/*   Updated: 2024/05/23 14:12:21 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}
/*
void	ft_print_list(t_list *lst)
{
	while (lst)
	{
		printf("%d -> ", *(int *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}

int	main(void)
{
	// Création d'une liste avec quelques éléments
	t_list *list = NULL;

	int *content1 = (int *)malloc(sizeof(int));
	int *content2 = (int *)malloc(sizeof(int));
	int *content3 = (int *)malloc(sizeof(int));
	if (!content1 || !content2 || !content3)
		return (1);

	*content1 = 42;
	*content2 = 21;
	*content3 = 84;

	t_list *node1 = ft_lstnew(content1);
	t_list *node2 = ft_lstnew(content2);
	t_list *node3 = ft_lstnew(content3);

	node1->next = node2;
	node2->next = node3;
	list = node1;

	printf("Avant clear:\n");
	ft_print_list(list);

	// Effacer toute la liste
	ft_lstclear(&list, del);

	printf("Après clear:\n");
	ft_print_list(list);  // Devrait afficher "NULL"

	return (0);
}*/