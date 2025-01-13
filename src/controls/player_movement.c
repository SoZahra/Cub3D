/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:33:49 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/13 14:22:49 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	move_forward(t_data *data, double new_x, double new_y)
{
	if (data->map[(int)new_y][(int)data->player.pos_x] != '1')
		data->player.pos_y = new_y;
	if (data->map[(int)data->player.pos_y][(int)new_x] != '1')
		data->player.pos_x = new_x;
}

void	handle_forward_movement(t_data *data)
{
	double	new_x;
	double	new_y;
	
	printf("Forward: %d, Backward: %d\n", 
           data->movement.forward, 
           data->movement.backward);
    printf("Player pos: (%f, %f)\n", 
           data->player.pos_x, 
           data->player.pos_y);

		   
	if (data->movement.forward)
	{
		new_x = data->player.pos_x + data->player.dir_x
			* data->movement.move_speed;
		new_y = data->player.pos_y + data->player.dir_y
			* data->movement.move_speed;
		move_forward(data, new_x, new_y);
	}
	if (data->movement.backward)
	{
		new_x = data->player.pos_x - data->player.dir_x
			* data->movement.move_speed;
		new_y = data->player.pos_y - data->player.dir_y
			* data->movement.move_speed;
		move_forward(data, new_x, new_y);
	}
}

static void	move_strafe(t_data *data, double new_x, double new_y)
{
	if (data->map[(int)new_y][(int)data->player.pos_x] != '1')
		data->player.pos_y = new_y;
	if (data->map[(int)data->player.pos_y][(int)new_x] != '1')
		data->player.pos_x = new_x;
}

void	handle_strafe_movement(t_data *data)
{
	double	new_x;
	double	new_y;
	double	perp_x;
	double	perp_y;

	perp_x = -data->player.dir_y;
	perp_y = data->player.dir_x;
	if (data->movement.right)
	{
		new_x = data->player.pos_x + perp_x * data->movement.move_speed;
		new_y = data->player.pos_y + perp_y * data->movement.move_speed;
		move_strafe(data, new_x, new_y);
	}
	if (data->movement.left)
	{
		new_x = data->player.pos_x - perp_x * data->movement.move_speed;
		new_y = data->player.pos_y - perp_y * data->movement.move_speed;
		move_strafe(data, new_x, new_y);
	}
}
