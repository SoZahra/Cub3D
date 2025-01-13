/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lizzieananifoli <lizzieananifoli@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:08:20 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/04 01:20:12 by lizzieanani      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	handle_rotation(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	if (data->movement.rot_right)
	{
		old_dir_x = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(-data->movement.rot_speed)
			- data->player.dir_y * sin(-data->movement.rot_speed);
		data->player.dir_y = old_dir_x * sin(-data->movement.rot_speed)
			+ data->player.dir_y * cos(-data->movement.rot_speed);
		old_plane_x = data->player.plane_x;
		data->player.plane_x = data->player.plane_x
			* cos(-data->movement.rot_speed) - data->player.plane_y
			* sin(-data->movement.rot_speed);
		data->player.plane_y = old_plane_x * sin(-data->movement.rot_speed)
			+ data->player.plane_y * cos(-data->movement.rot_speed);
	}
	handle_rotation_left(data);
}

void	handle_rotation_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	if (data->movement.rot_left)
	{
		old_dir_x = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(data->movement.rot_speed)
			- data->player.dir_y * sin(data->movement.rot_speed);
		data->player.dir_y = old_dir_x * sin(data->movement.rot_speed)
			+ data->player.dir_y * cos(data->movement.rot_speed);
		old_plane_x = data->player.plane_x;
		data->player.plane_x = data->player.plane_x
			* cos(data->movement.rot_speed) - data->player.plane_y
			* sin(data->movement.rot_speed);
		data->player.plane_y = old_plane_x * sin(data->movement.rot_speed)
			+ data->player.plane_y * cos(data->movement.rot_speed);
	}
}
