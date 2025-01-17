/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:34:26 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/17 18:58:51 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	count_door_in_row(t_data *data, int i, int j, int *count)
{
	if (j >= data->map_width)
		return ;
	if (data->map[i][j] == 'D')
		(*count)++;
	count_door_in_row(data, i, j + 1, count);
}

static void	count_doors_recursive(t_data *data, int i, int *count)
{
	if (i >= data->map_height)
		return ;
	count_door_in_row(data, i, 0, count);
	count_doors_recursive(data, i + 1, count);
}

static void	init_door(t_door *door, int x, int y)
{
	door->x = x;
	door->y = y;
	door->is_open = 0;
	door->animation = 0.0;
}

static void	fill_door_in_row(t_data *data, int i, int j, int *count)
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

static void	fill_doors_recursive(t_data *data, int i, int *count)
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

// void	handle_door(t_data *data)
// {
// 	int	player_x;
// 	int	player_y;
// 	int	i;

// 	player_x = (int)data->player.pos_x;
// 	player_y = (int)data->player.pos_y;
// 	i = 0;
// 	while (i < data->num_doors)
// 	{
// 		if (abs(player_x - data->doors[i].x) <= 1 && abs(player_y
// 				- data->doors[i].y) <= 1)
// 		{
// 			if (data->keys.e)
// 			{
// 				data->doors[i].is_open = !data->doors[i].is_open;
// 			}
// 		}
// 		i++;
// 	}
// }

void	handle_door(t_data *data)
{
	int			player_x;
	int			player_y;
	int			i;
	static int	last_e_state = 0;

	player_x = (int)data->player.pos_x;
	player_y = (int)data->player.pos_y;
	i = 0;
	while (i < data->num_doors)
	{
		if (abs(player_x - data->doors[i].x) <= 1 && abs(player_y
				- data->doors[i].y) <= 1)
		{
			if (data->keys.e && !last_e_state)
			{
				data->doors[i].is_open = !data->doors[i].is_open;
			}
		}
		i++;
	}
	last_e_state = data->keys.e;
}

// void	update_doors(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->num_doors)
// 	{
// 		if (data->doors[i].is_open && data->doors[i].animation < 1.0)
// 			data->doors[i].animation += 0.05;
// 		else if (!data->doors[i].is_open && data->doors[i].animation > 0.0)
// 			data->doors[i].animation -= 0.05;
// 		i++;
// 	}
// }

void	update_doors(t_data *data)
{
	int		i;
	double	animation_speed;

	animation_speed = 0.05;  // Vous pouvez ajuster cette valeur
	i = 0;
	while (i < data->num_doors)
	{
		if (data->doors[i].is_open)  // Si la porte est ouverte
		{
			if (data->doors[i].animation < 1.0)  // Si l'animation n'est pas terminée
			{
				data->doors[i].animation += animation_speed;
				if (data->doors[i].animation > 1.0)
					data->doors[i].animation = 1.0;
			}
		}
		else  // Si la porte est fermée
		{
			if (data->doors[i].animation > 0.0)  // Si l'animation n'est pas terminée
			{
				data->doors[i].animation -= animation_speed;
				if (data->doors[i].animation < 0.0)
					data->doors[i].animation = 0.0;
			}
		}
		i++;
	}
}

int	load_door_textures(t_data *data)
{
	int	i;

	i = 0;
	char *paths[] = {
		"textures/door_0.xpm",
		"textures/door_1.xpm",
		"textures/door_2.xpm",
		"textures/door_3.xpm",
		"textures/door_4.xpm",
		"textures/door_5.xpm",
		"textures/door_6.xpm",
		"textures/door_7.xpm",
	};
	data->door_tex.num_frames = 8;
	while (i < data->door_tex.num_frames)
	{
		if (!load_texture(data, &data->door_tex.frames[i], paths[i]))
			return (0);
		i++;
	}
	return (1);
}
