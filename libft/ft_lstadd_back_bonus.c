/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:36:48 by fzayani           #+#    #+#             */
/*   Updated: 2024/05/24 13:39:52 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*nv_noeud;

	if (*lst)
	{
		nv_noeud = ft_lstlast(*lst);
		nv_noeud->next = new;
	}
	else
		*lst = new;
}
