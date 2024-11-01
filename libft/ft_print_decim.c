/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_decim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:25:18 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/09 17:38:40 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_printf(long nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		i += ft_putchar_printf('-');
		nb = -nb;
	}
	if (nb > 9)
	{
		i += ft_putnbr_printf(nb / 10);
	}
	i += ft_putchar_printf((nb % 10) + '0');
	return (i);
}
