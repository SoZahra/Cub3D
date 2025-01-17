/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:08:20 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/17 11:50:39 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	rotate_vectors(t_data *data, double angle)
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

static void	update_ray_vectors(t_data *data)
{
	data->ray.dir_x = data->player.dir_x;
	data->ray.dir_y = data->player.dir_y;
	data->ray.plane_x = data->player.plane_x;
	data->ray.plane_y = data->player.plane_y;
}

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

int	is_door_closed(t_data *data, int x, int y)
{
	int	i;

	if (data->map[y][x] == 'D')
	{
		i = 0;
		while (i < data->num_doors)
		{
			if (data->doors[i].x == x && data->doors[i].y == y)
			{
				if (!data->doors[i].is_open)
					return (1);
				break ;
			}
			i++;
		}
	}
	return (0);
}

static void	update_player_pos(t_data *data, double move_x, double move_y)
{
	int	next_x;
	int	next_y;

	next_x = (int)(data->player.pos_x + move_x);
	next_y = (int)(data->player.pos_y + move_y);
	if (data->map[(int)data->player.pos_y][next_x] != '1'
		&& !is_door_closed(data, next_x, (int)data->player.pos_y))
		data->player.pos_x += move_x;
	if (data->map[next_y][(int)data->player.pos_x] != '1'
		&& !is_door_closed(data, (int)data->player.pos_x, next_y))
		data->player.pos_y += move_y;
}

static double	adjust_speed(t_data *data)
{
	double	move_speed;

	move_speed = data->movement.move_speed;
	if ((data->movement.forward || data->movement.backward)
		&& (data->movement.left || data->movement.right))
		move_speed /= sqrt(2);
	return (move_speed);
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

void	update_strafe_pos(t_data *data, double move_x, double move_y)
{
	int	next_x;
	int	next_y;

	next_x = (int)(data->player.pos_x + move_x);
	next_y = (int)(data->player.pos_y + move_y);
	if (data->map[(int)data->player.pos_y][next_x] != '1'
		&& !is_door_closed(data, next_x, (int)data->player.pos_y))
		data->player.pos_x += move_x;
	if (data->map[next_y][(int)data->player.pos_x] != '1'
		&& !is_door_closed(data, (int)data->player.pos_x, next_y))
		data->player.pos_y += move_y;
}

static double	adjust_strafe_speed(t_data *data)
{
	double	move_speed;

	move_speed = data->movement.move_speed;
	if ((data->movement.forward || data->movement.backward)
		&& (data->movement.left || data->movement.right))
		move_speed /= sqrt(2);
	return (move_speed);
}

static void	move_left(t_data *data, double move_speed)
{
	double	move_x;
	double	move_y;

	move_x = -data->player.plane_x * move_speed;
	move_y = -data->player.plane_y * move_speed;
	update_strafe_pos(data, move_x, move_y);
}

static void	move_right(t_data *data, double move_speed)
{
	double	move_x;
	double	move_y;

	move_x = data->player.plane_x * move_speed;
	move_y = data->player.plane_y * move_speed;
	update_strafe_pos(data, move_x, move_y);
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
