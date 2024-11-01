/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:50:54 by fzayani           #+#    #+#             */
/*   Updated: 2024/05/23 20:00:12 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nv_noeud;

	nv_noeud = malloc(sizeof(t_list));
	if (!nv_noeud)
		return (NULL);
	nv_noeud->content = content;
	nv_noeud->next = NULL;
	return (nv_noeud);
}
/*
int	main(void)
{
	t_list *nv_list = ft_lstnew("salut");

	printf("%s\n", (char *)nv_list->content);
}*/