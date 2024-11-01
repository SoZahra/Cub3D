/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:15:11 by fzayani           #+#    #+#             */
/*   Updated: 2024/05/23 19:44:55 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int occ)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)occ)
			return ((char *)str + i);
		i++;
	}
	if (str[i] == (unsigned char)occ)
		return ((char *)str + i);
	return (NULL);
}
