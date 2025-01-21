/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:49:58 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/21 11:37:50 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	init_ray_dir(t_ray *ray, t_data *data, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = data->player.dir_x + ray->plane_x * ray->camera_x;
	ray->ray_dir_y = data->player.dir_y + ray->plane_y * ray->camera_x;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
}

void	init_ray_position(t_ray *ray, t_data *data)
{
	if (!ray || !data)
		return ;
	ray->pos_x = (double)data->player.pos_x + 0.5;
	ray->pos_y = (double)data->player.pos_y + 0.5;
}

void	init_ray_dist(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	init_ray_step(t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

void	init_movement_values(t_data *data)
{
	data->movement.move_speed = 0.1;
	data->movement.rot_speed = 0.05;
	data->movement.forward = 0;
	data->movement.backward = 0;
	data->movement.left = 0;
	data->movement.right = 0;
	data->movement.rot_left = 0;
	data->movement.rot_right = 0;
	data->movement.mouse_x = WIN_WIDTH / 2;
	data->movement.prev_mouse_x = WIN_WIDTH / 2;
}
