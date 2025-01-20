/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:08:20 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/20 17:23:32 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	handle_rotation(t_data *data)
{
	double	rot_speed;

	if (!data)
		return ;
	rot_speed = data->movement.rot_speed;
	if (data->movement.rot_left)
		rotate_vectors(data, rot_speed);
	if (data->movement.rot_right)
		rotate_vectors(data, -rot_speed);
	update_ray_vectors(data);
}

static void	move_forward(t_data *data, double move_speed)
{
	double	move_x;
	double	move_y;

	move_x = data->player.dir_x * move_speed;
	move_y = data->player.dir_y * move_speed;
	update_player_pos(data, move_x, move_y);
}

static void	move_backward(t_data *data, double move_speed)
{
	double	move_x;
	double	move_y;

	move_x = -data->player.dir_x * move_speed;
	move_y = -data->player.dir_y * move_speed;
	update_player_pos(data, move_x, move_y);
}

void	handle_forward_movement(t_data *data)
{
	double	move_speed;

	if (!data)
		return ;
	move_speed = adjust_speed(data);
	if (data->movement.forward)
		move_forward(data, move_speed);
	if (data->movement.backward)
		move_backward(data, move_speed);
}

void	handle_strafe_movement(t_data *data)
{
	double	move_speed;

	if (!data)
		return ;
	move_speed = adjust_strafe_speed(data);
	if (data->movement.left)
		move_left(data, move_speed);
	if (data->movement.right)
		move_right(data, move_speed);
}
