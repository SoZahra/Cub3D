/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:12:33 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/09 17:39:13 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_p(unsigned long address)
{
	char	*base;
	int		i;

	i = 0;
	base = "0123456789abcdef";
	if (!address)
		return (ft_putstr_printf("(nil)"));
	if (address >= 16)
		i += ft_print_p(address / 16);
	i += ft_putchar_printf(base[address % 16]);
	return (i);
}
