/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:34:26 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/22 11:26:52 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	init_doors(t_data *data)
{
	int	count;

	if (!data || !data->map)
		return (0);
	if (!validate_doors(data))
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
	int			player_x;
	int			player_y;
	int			i;
	static int	last_e_state = 0;

	if (!data)
		return ;
	if (!data->doors || data->num_doors <= 0)
		return ;
	player_x = (int)data->player.pos_x;
	player_y = (int)data->player.pos_y;
	i = 0;
	while (i < data->num_doors)
	{
		if (abs(player_x - data->doors[i].x) <= 1 && abs(player_y
				- data->doors[i].y) <= 1)
		{
			if (data->keys.e && !last_e_state)
				data->doors[i].is_open = !data->doors[i].is_open;
		}
		i++;
	}
	last_e_state = data->keys.e;
}

void	update_doors_2(t_data *data)
{
	int		i;
	double	animation_speed;

	animation_speed = 0.05;
	i = 0;
	if (data->doors[i].animation > 0.0)
	{
		data->doors[i].animation -= animation_speed;
		if (data->doors[i].animation < 0.0)
			data->doors[i].animation = 0.0;
	}
}

void	update_doors(t_data *data)
{
	int		i;
	double	animation_speed;

	animation_speed = 0.05;
	i = 0;
	while (i < data->num_doors)
	{
		if (data->doors[i].is_open)
		{
			if (data->doors[i].animation < 1.0)
			{
				data->doors[i].animation += animation_speed;
				if (data->doors[i].animation > 1.0)
					data->doors[i].animation = 1.0;
			}
		}
		else
			update_doors_2(data);
		i++;
	}
}

void	update_wall_animation(t_data *data)
{
	data->wall_tex.animation_time += 0.1;
	if (data->wall_tex.animation_time >= data->wall_tex.num_frames)
		data->wall_tex.animation_time = 0.0;
}
