/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:00:31 by fzayani           #+#    #+#             */
/*   Updated: 2024/05/22 18:01:14 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destlen)
{
	size_t	srclen;
	size_t	i;

	if (destlen == 0)
		return (ft_strlen(src));
	srclen = ft_strlen(src);
	i = 0;
	while (src[i] != '\0' && i < (destlen - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srclen);
}
