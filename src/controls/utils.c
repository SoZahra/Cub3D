/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:20:27 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/20 17:26:23 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

double	adjust_speed(t_data *data)
{
	double	move_speed;

	move_speed = data->movement.move_speed;
	if ((data->movement.forward || data->movement.backward)
		&& (data->movement.left || data->movement.right))
		move_speed /= sqrt(2);
	return (move_speed);
}

void	update_player_pos(t_data *data, double move_x, double move_y)
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

double	adjust_strafe_speed(t_data *data)
{
	double	move_speed;

	move_speed = data->movement.move_speed;
	if ((data->movement.forward || data->movement.backward)
		&& (data->movement.left || data->movement.right))
		move_speed /= sqrt(2);
	return (move_speed);
}

int	is_door_closed(t_data *data, int x, int y)
{
	int	i;

	if (!data)
		return (0);
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
