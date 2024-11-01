/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_unsig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:34:10 by fzayani           #+#    #+#             */
/*   Updated: 2024/10/08 10:34:27 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_unsigned_num_len(unsigned int n)
{
	int	len = 1;

	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa_unsigned(unsigned int n)
{
	int		len;
	char	*str;

	len = ft_unsigned_num_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';  // Terminer la chaîne par le caractère nul
	while (len > 0)
	{
		str[--len] = (n % 10) + '0';  // Obtenir le dernier chiffre
		n /= 10;  // Réduire le nombre
	}
	return (str);
}
