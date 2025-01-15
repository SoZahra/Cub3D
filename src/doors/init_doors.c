/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:34:26 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/15 17:30:55 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	init_doors(t_data *data)
{
	int	count;
	int i;
	int j;

	count = ((i = 0));
	while(i < data->map_height)
	{
		j = 0;
		while(j < data->map_width)
		{
			if (data->map[i][j] == 'D')
				count++;
			j++;
		}
		i++;
	}
	data->doors = malloc(sizeof(t_door) * count);
	if (!data->doors)
		return (0);
	count = ((i = 0));
	while(i < data->map_height)
	{
		j= 0;
		while(j < data->map_width)
		{
			if (data->map[i][j] == 'D')
			{
				data->doors[count].x = j;
				data->doors[count].y = i;
				data->doors[count].is_open = 0;
				data->doors[count].animation = 0.0;
				count++;
			}
			j++;
		}
		i++;
	}
	data->num_doors = count;
	return (1);
}

void	handle_door(t_data *data)
{
	int	player_x;
	int	player_y;
    int i;

	player_x = (int)data->player.pos_x;
	player_y = (int)data->player.pos_y;
    i = 0;
    while(i < data->num_doors)
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
    int i;

    i = 0;
	while(i < data->num_doors)
	{
		if (data->doors[i].is_open && data->doors[i].animation < 1.0)
			data->doors[i].animation += 0.05;
		else if (!data->doors[i].is_open && data->doors[i].animation > 0.0)
			data->doors[i].animation -= 0.05;
		i++;
	}
}
