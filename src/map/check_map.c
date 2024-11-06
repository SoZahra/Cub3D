/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:58:38 by fzayani           #+#    #+#             */
/*   Updated: 2024/11/05 13:48:55 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	check_map_walls(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_width)
	{
		if (data->map[0][i] != '1' || data->map[data->map_height - 1][i] != '1')
			return (printf("Error: Map must be surrounded by walls.\n"), 0);
		i++;
	}
	i = 0;
	while (i < data->map_height)
	{
		if (data->map[i][0] != '1' || data->map[i][data->map_width - 1] != '1')
		{
			printf("%d - %c\n", i, data->map[i][0]);
			printf("%d %d - %c\n", i, data->map_width,
				data->map[i][data->map_width - 1]);
			printf("Error: Map must be surrounded by walls.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	check_map(t_data *data)
{
	if (!check_map_elements(data))
	{
		free_map(data);
		error_exit("Error : Map doesn't have valid char !!!");
	}
	if (!check_map_walls(data))
	{
		free_map(data);
		error_exit("Error : Map doesn't have walls !!! wtf");
	}
}

