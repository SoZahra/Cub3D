/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:53:14 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/09 17:39:23 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_printf(const char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (ft_putstr_printf("(null)"));
	while (str[i])
	{
		ft_putchar_printf(str[i]);
		i++;
	}
	return (i);
}
