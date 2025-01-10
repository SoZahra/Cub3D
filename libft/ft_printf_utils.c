/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:06:01 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/10 12:03:36 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_printf_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putstr_printf_fd(const char *str, int fd)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (write(fd, str, len));
}

int	ft_putnbr_base_printf_fd(unsigned long nbr, const char *base, int fd)
{
	int	base_len;
	int	count;

	count = 0;
	base_len = ft_strlen(base);
	if (base_len < 2)
		return (0);
	if (nbr >= (unsigned long)base_len)
		count += ft_putnbr_base_printf_fd(nbr / base_len, base, fd);
	count += ft_putchar_printf_fd(base[nbr % base_len], fd);
	return (count);
}

int	ft_putnbr_printf_fd(int n, int fd)
{
	char	*num_str;
	int		len;

	num_str = ft_itoa(n);
	len = ft_putstr_printf_fd(num_str, fd);
	free(num_str);
	return (len);
}
