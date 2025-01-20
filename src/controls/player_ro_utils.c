/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_ro_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:20:25 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/20 17:21:45 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	rotate_vectors(t_data *data, double angle)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(angle) - data->player.dir_y
		* sin(angle);
	data->player.dir_y = old_dirx * sin(angle) + data->player.dir_y
		* cos(angle);
	old_planex = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(angle)
		- data->player.plane_y * sin(angle);
	data->player.plane_y = old_planex * sin(angle) + data->player.plane_y
		* cos(angle);
}

void	update_ray_vectors(t_data *data)
{
	data->ray.dir_x = data->player.dir_x;
	data->ray.dir_y = data->player.dir_y;
	data->ray.plane_x = data->player.plane_x;
	data->ray.plane_y = data->player.plane_y;
}

void	move_left(t_data *data, double move_speed)
{
	double	move_x;
	double	move_y;

	move_x = -data->player.plane_x * move_speed;
	move_y = -data->player.plane_y * move_speed;
	update_strafe_pos(data, move_x, move_y);
}

void	move_right(t_data *data, double move_speed)
{
	double	move_x;
	double	move_y;

	move_x = data->player.plane_x * move_speed;
	move_y = data->player.plane_y * move_speed;
	update_strafe_pos(data, move_x, move_y);
}
