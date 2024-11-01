/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:59:47 by fzayani           #+#    #+#             */
/*   Updated: 2024/05/21 17:19:11 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	if (!src && !dest)
		return (NULL);
	if (src > dest)
		dest = ft_memcpy(dest, src, len);
	else
	{
		while (len--)
			d[len] = s[len];
	}
	return (dest);
}
