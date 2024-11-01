/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:09:50 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/09 17:39:06 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_printf(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_rev_printf(char *str)
{
	int	i;

	i = ft_strlen_printf(str) - 1;
	while (i >= 0)
	{
		ft_putchar_printf(str[i]);
		i--;
	}
}

int	ft_putnbr_base_printf(long int nbr, char *base)
{
	int	len;
	int	base_len;

	len = 0;
	base_len = ft_strlen_printf(base);
	if (nbr < 0)
	{
		len += ft_putchar_printf('-');
		nbr = -nbr;
	}
	if (nbr >= base_len)
		len += ft_putnbr_base_printf(nbr / base_len, base);
	len += ft_putchar_printf(base[nbr % base_len]);
	return (len);
}
