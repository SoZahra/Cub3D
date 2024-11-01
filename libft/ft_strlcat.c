/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:01:29 by fzayani           #+#    #+#             */
/*   Updated: 2024/05/22 18:15:00 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	x;
	size_t	lend;
	size_t	lens;

	x = 0;
	lens = ft_strlen(src);
	while (dest[x] != '\0' && x < size)
	{
		x++;
	}
	lend = x;
	if (size == x)
	{
		return (lens + x);
	}
	if (lens < size - lend)
		ft_memcpy(dest + lend, src, lens + 1);
	else
	{
		ft_memcpy(dest + lend, src, size - lend - 1);
		dest[size - 1] = '\0';
	}
	return (lend + lens);
}
