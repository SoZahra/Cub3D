/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:34:26 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/21 19:28:23 by fzayani          ###   ########.fr       */
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

int	load_door_textures(t_data *data)
{
	int		i;
	char	*paths[8];

	i = 0;
	paths[0] = "textures/door_0.xpm";
	paths[1] = "textures/door_1.xpm";
	paths[2] = "textures/door_2.xpm";
	paths[3] = "textures/door_3.xpm";
	paths[4] = "textures/door_4.xpm";
	paths[5] = "textures/door_5.xpm";
	paths[6] = "textures/door_6.xpm";
	paths[7] = "textures/door_7.xpm";
	data->door_tex.num_frames = 8;
	while (i < data->door_tex.num_frames)
	{
		if (!load_texture(data, &data->door_tex.frames[i], paths[i]))
			return (0);
		i++;
	}
	return (1);
}
