/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:30:48 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/21 19:58:32 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	count_door_in_row(t_data *data, int i, int j, int *count)
{
	if (j >= data->map_width)
		return ;
	if (data->map[i][j] == 'D')
		(*count)++;
	count_door_in_row(data, i, j + 1, count);
}

void	count_doors_recursive(t_data *data, int i, int *count)
{
	if (i >= data->map_height)
		return ;
	count_door_in_row(data, i, 0, count);
	count_doors_recursive(data, i + 1, count);
}

void	init_door(t_door *door, int x, int y)
{
	door->x = x;
	door->y = y;
	door->is_open = 0;
}

void	fill_door_in_row(t_data *data, int i, int j, int *count)
{
	if (j >= data->map_width)
		return ;
	if (data->map[i][j] == 'D')
	{
		init_door(&data->doors[*count], j, i);
		(*count)++;
	}
	fill_door_in_row(data, i, j + 1, count);
}

void	fill_doors_recursive(t_data *data, int i, int *count)
{
	if (i >= data->map_height)
		return ;
	fill_door_in_row(data, i, 0, count);
	fill_doors_recursive(data, i + 1, count);
}
