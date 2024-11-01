/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:46:42 by fzayani           #+#    #+#             */
/*   Updated: 2024/05/23 13:34:15 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}
/*
int	main(void)
{
	int *content = (int *)malloc(sizeof(int));
	if (!content)
		return (1);
	*content = 42;

	t_list *node = ft_lstnew(content);
	if (!node)
	{
		free(content);
		return (1);
	}

	printf("Avant suppression:\n");
	printf("Adresse du noeud: %p\n", (void *)node);
	printf("Adresse du contenu: %p\n", (void *)node->content);
	printf("Valeur du contenu: %d\n", *(int *)node->content);

	printf("Après suppression:\n");
	printf("Le noeud a été supprimé.\n");

	return (0);
}*/