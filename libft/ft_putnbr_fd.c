/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:37:19 by fzayani           #+#    #+#             */
/*   Updated: 2024/05/22 16:16:45 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr > 9)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putchar_fd(nbr % 10 + '0', fd);
	}
	else
		ft_putchar_fd('0' + nbr, fd);
}
/*
int	main(void)
{
	int num = -12345; // Exemple de nombre à afficher
	printf("Affichage de %d avec ft_putnbr_fd :\n", num);
	ft_putnbr_fd(num, STDOUT_FILENO);
		// Utilisation de STDOUT_FILENO pour afficher sur la sortie standard

	printf("\n");
	return (0);
}*/