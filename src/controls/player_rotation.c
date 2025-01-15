/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:08:20 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/15 16:38:58 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	handle_rotation(t_data *data)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rotSpeed;

	rotSpeed = data->movement.rot_speed;
	if (data->movement.rot_left)
	{
		oldDirX = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(rotSpeed)
			- data->player.dir_y * sin(rotSpeed);
		data->player.dir_y = oldDirX * sin(rotSpeed) + data->player.dir_y
			* cos(rotSpeed);
		oldPlaneX = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(rotSpeed)
			- data->player.plane_y * sin(rotSpeed);
		data->player.plane_y = oldPlaneX * sin(rotSpeed) + data->player.plane_y
			* cos(rotSpeed);
	}
	if (data->movement.rot_right)
	{
		oldDirX = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(-rotSpeed)
			- data->player.dir_y * sin(-rotSpeed);
		data->player.dir_y = oldDirX * sin(-rotSpeed) + data->player.dir_y
			* cos(-rotSpeed);
		oldPlaneX = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(-rotSpeed)
			- data->player.plane_y * sin(-rotSpeed);
		data->player.plane_y = oldPlaneX * sin(-rotSpeed) + data->player.plane_y
			* cos(-rotSpeed);
	}
	data->ray.dir_x = data->player.dir_x;
	data->ray.dir_y = data->player.dir_y;
	data->ray.plane_x = data->player.plane_x;
	data->ray.plane_y = data->player.plane_y;
}

void	handle_forward_movement(t_data *data)
{
	double	move_speed;

	move_speed = data->movement.move_speed;
	if ((data->movement.forward || data->movement.backward)
		&& (data->movement.left || data->movement.right))
		move_speed /= sqrt(2);
	if (data->movement.forward)
	{
		if (data->map[(int)data->player.pos_y][(int)(data->player.pos_x
				+ data->player.dir_x * move_speed)] != '1')
			data->player.pos_x += data->player.dir_x * move_speed;
		if (data->map[(int)(data->player.pos_y + data->player.dir_y
				* move_speed)][(int)data->player.pos_x] != '1')
			data->player.pos_y += data->player.dir_y * move_speed;
	}
	if (data->movement.backward)
	{
		if (data->map[(int)data->player.pos_y][(int)(data->player.pos_x
				- data->player.dir_x * move_speed)] != '1')
			data->player.pos_x -= data->player.dir_x * move_speed;
		if (data->map[(int)(data->player.pos_y - data->player.dir_y
				* move_speed)][(int)data->player.pos_x] != '1')
			data->player.pos_y -= data->player.dir_y * move_speed;
	}
}

void	handle_strafe_movement(t_data *data)
{
	double	move_speed;
	double	plane_x;
	double	plane_y;

	move_speed = data->movement.move_speed;
	plane_x = data->player.plane_x;
	plane_y = data->player.plane_y;
	if ((data->movement.forward || data->movement.backward)
		&& (data->movement.left || data->movement.right))
		move_speed /= sqrt(2);
	if (data->movement.left)
	{
		if (data->map[(int)data->player.pos_y][(int)(data->player.pos_x
				- plane_x * move_speed)] != '1')
			data->player.pos_x -= plane_x * move_speed;
		if (data->map[(int)(data->player.pos_y - plane_y
				* move_speed)][(int)data->player.pos_x] != '1')
			data->player.pos_y -= plane_y * move_speed;
	}
	if (data->movement.right)
	{
		if (data->map[(int)data->player.pos_y][(int)(data->player.pos_x
				+ plane_x * move_speed)] != '1')
			data->player.pos_x += plane_x * move_speed;
		if (data->map[(int)(data->player.pos_y + plane_y
				* move_speed)][(int)data->player.pos_x] != '1')
			data->player.pos_y += plane_y * move_speed;
	}
}
