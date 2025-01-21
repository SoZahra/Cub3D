/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:34:26 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/16 17:33:36 by lanani-f         ###   ########.fr       */
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
	door->animation = 0.0;
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

int	init_doors(t_data *data)
{
	int	count;

	if (!data || !data->map)
		return (0);
	count = 0;
	count_doors_recursive(data, 0, &count);
	if (count == 0)
	{
		data->doors = NULL;
		data->num_doors = 0;
		return (1);
	}
	data->doors = malloc(sizeof(t_door) * count);
	if (!data->doors)
		return (0);
	count = 0;
	fill_doors_recursive(data, 0, &count);
	data->num_doors = count;
	return (1);
}

void	handle_door(t_data *data)
{
	int	player_x;
	int	player_y;
	int	i;

	player_x = (int)data->player.pos_x;
	player_y = (int)data->player.pos_y;
	i = 0;
	while (i < data->num_doors)
	{
		if (abs(player_x - data->doors[i].x) <= 1 && abs(player_y
				- data->doors[i].y) <= 1)
		{
			if (data->keys.e)
			{
				data->doors[i].is_open = !data->doors[i].is_open;
			}
		}
		i++;
	}
}

void	update_doors(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_doors)
	{
		if (data->doors[i].is_open && data->doors[i].animation < 1.0)
			data->doors[i].animation += 0.05;
		else if (!data->doors[i].is_open && data->doors[i].animation > 0.0)
			data->doors[i].animation -= 0.05;
		i++;
	}
}
