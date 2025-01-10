/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:04:35 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/10 12:03:06 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_unsigned_printf_fd(unsigned int n, int fd)
{
	char	*num_str;
	int		len;

	num_str = ft_itoa_unsigned(n);
	len = ft_putstr_printf_fd(num_str, fd);
	free(num_str);
	return (len);
}

int	ft_aff_p_fd(va_list args, int fd)
{
	int				i;
	unsigned long	address;

	i = 0;
	address = va_arg(args, unsigned long);
	if (address)
		i += ft_putstr_printf_fd("0x", fd);
	i += ft_putnbr_base_printf_fd(address, "0123456789abcdef", fd);
	return (i);
}

int	ft_check_format_fd(char str, va_list args, int fd)
{
	int	i;

	i = 0;
	if (str == 'c')
		i += ft_putchar_printf_fd(va_arg(args, int), fd);
	else if (str == 's')
		i += ft_putstr_printf_fd(va_arg(args, char *), fd);
	else if (str == 'd' || str == 'i')
		i += ft_putnbr_printf_fd(va_arg(args, int), fd);
	else if (str == 'u')
		i += ft_putnbr_unsigned_printf_fd(va_arg(args, unsigned int), fd);
	else if (str == 'x')
		i += ft_putnbr_base_printf_fd(va_arg(args, unsigned int),
				"0123456789abcdef", fd);
	else if (str == 'X')
		i += ft_putnbr_base_printf_fd(va_arg(args, unsigned int),
				"0123456789ABCDEF", fd);
	else if (str == 'p')
		i += ft_aff_p_fd(args, fd);
	else if (str == '%')
		i += ft_putchar_printf_fd('%', fd);
	return (i);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	int		i;
	int		stock;
	va_list	args;

	i = ((stock = 0));
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			stock += ft_check_format_fd(format[i + 1], args, fd);
			i++;
		}
		else
			stock += ft_putchar_printf_fd(format[i], fd);
		i++;
	}
	va_end(args);
	return (stock);
}
