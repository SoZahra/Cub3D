/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:50:41 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/10 14:02:05 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_aff_p(va_list args)
{
	int				i;
	unsigned long	address;

	i = 0;
	address = va_arg(args, unsigned long);
	if (address)
		i += ft_putstr_printf("0x");
	i += ft_print_p(address);
	return (i);
}

static int	ft_check_format(char str, va_list args)
{
	int	i;

	i = 0;
	if (str == 'c')
		i += ft_putchar_printf(va_arg(args, int));
	if (str == 's')
		i += ft_putstr_printf(va_arg(args, char *));
	if (str == 'd' || str == 'i')
		i += ft_putnbr_printf(va_arg(args, int));
	if (str == 'u')
		i += ft_putnbr_printf(va_arg(args, unsigned int));
	if (str == 'x')
		i += ft_putnbr_base_printf(va_arg(args, unsigned int),
				"0123456789abcdef");
	if (str == 'X')
		i += ft_putnbr_base_printf(va_arg(args, unsigned int),
				"0123456789ABCDEF");
	if (str == 'p')
		i += ft_aff_p(args);
	if (str == '%')
		i += ft_putchar_printf('%');
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		stock;
	va_list	args;

	if (!format)
		return (-1);
	i = 0;
	stock = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			stock += ft_check_format(format[i + 1], args);
			i++;
		}
		else
		{
			stock += ft_putchar_printf(format[i]);
		}
		i++;
	}
	va_end(args);
	return (stock);
}
/*
#include <stdio.h>
int	main(void)
{
	int	a;

	a = 42;
	if (printf("") == ft_printf(""))
		printf("OK\n");
	else
		printf("KO\n");
}*/