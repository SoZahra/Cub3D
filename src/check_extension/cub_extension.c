/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_extension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:48:40 by fzayani           #+#    #+#             */
/*   Updated: 2024/11/01 18:11:44 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	cub_extension(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	return (len > 4 && ft_strcmp(filename + len - 4, ".cub") == 0);
}
int	check_arguments(int ac, char **av)
{
	if (ac != 2)
	{
		ft_printf("Error: Wrong number of arguments.\n");
		ft_printf("Usage: ./cub3d map.cub\n");
		return (0);
	}
	if (!cub_extension(av[1]))
	{
		ft_printf("Error: The map file must have a .cub extension.\n");
		return (0);
	}
	return (1);
}
