/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:50:47 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/20 17:03:37 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	set_direction_north(t_ray *ray)
{
	ray->dir_x = 0;
	ray->dir_y = -1;
	ray->plane_x = 0.66;
	ray->plane_y = 0;
}

void	set_direction_vectors_(t_ray *ray, char dir)
{
	if (dir == 'N')
		set_direction_north(ray);
	else if (dir == 'S')
	{
		ray->dir_x = 0;
		ray->dir_y = 1;
		ray->plane_x = -0.66;
		ray->plane_y = 0;
	}
	else if (dir == 'E')
	{
		ray->dir_x = 1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		ray->dir_x = -1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = -0.66;
	}
}

void	update_player_vectors(t_ray *ray, t_data *data)
{
	data->player.dir_x = ray->dir_x;
	data->player.dir_y = ray->dir_y;
	data->player.plane_x = ray->plane_x;
	data->player.plane_y = ray->plane_y;
}

void	init_player_pos(t_ray *ray, t_data *data)
{
	if (!ray || !data)
		return ;
	init_ray_position(ray, data);
	set_direction_vectors_(ray, data->player.player_dir);
	update_player_vectors(ray, data);
	init_movement_values(data);
}

void	calculate_texture_coords(t_floor *floor, t_data *data, int x, int y)
{
	floor->tex_x = (int)(floor->floor_x * data->floor.width)
		% data->floor.width;
	floor->tex_y = (int)(floor->floor_y * data->floor.height)
		% data->floor.height;
	floor->player_distance = sqrt(pow(x - (WIN_WIDTH / 2), 2) + pow(y
				- (WIN_HEIGHT / 2), 2)) / 100.0;
}
