/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:05:38 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/20 17:06:04 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_floor_values(t_floor *floor, t_data *data, int x, int y)
{
	floor->pos_z = 0.5 * WIN_HEIGHT;
	floor->row_distance = floor->pos_z / (y - WIN_HEIGHT / 2.0);
	floor->floor_x = data->player.pos_x + floor->row_distance
		* (data->player.dir_x + data->player.plane_x * (2.0 * x / WIN_WIDTH
				- 1));
	floor->floor_y = data->player.pos_y + floor->row_distance
		* (data->player.dir_y + data->player.plane_y * (2.0 * x / WIN_WIDTH
				- 1));
}

int	get_floor_color(t_floor *floor, t_data *data)
{
	if (data->f_is_texture)
	{
		floor->color = get_tex_color(&data->floor, floor->tex_x, floor->tex_y);
		return (apply_lighting(floor->color, floor->player_distance));
	}
	floor->color = data->f_color;
	return (apply_lighting(floor->color, floor->player_distance));
}

void	draw_floor(t_data *data, int x, int y)
{
	t_floor	floor;

	if ((y * WIN_WIDTH + x) >= (WIN_WIDTH * WIN_HEIGHT))
		return ;
	if (data->f_is_texture)
	{
		init_floor_values(&floor, data, x, y);
		calculate_texture_coords(&floor, data, x, y);
	}
	else
	{
		floor.player_distance = sqrt(pow(x - (WIN_WIDTH / 2), 2) + pow(y
					- (WIN_HEIGHT / 2), 2)) / 100.0;
	}
	data->img.addr[y * WIN_WIDTH + x] = get_floor_color(&floor, data);
}
