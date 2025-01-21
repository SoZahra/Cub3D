/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:47:25 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/21 19:30:44 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	update_ray_position(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

int	check_wall_collision(t_ray *ray, t_data *data)
{
	if (ray->map_x < 0 || ray->map_x >= data->map_width || ray->map_y < 0
		|| ray->map_y >= data->map_height
		|| data->map[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

// int	check_door_surroundings(t_data *data, int y, int x)
// {
// 	if (y == 0 || x == 0 || y == data->map_height - 1
// 		|| x >= (int)ft_strlen(data->map[y]) - 1)
// 		return (error_exit("Error: Door position invalid (at border)"), 0);
// 	if (data->map[y - 1][x] != '1' || data->map[y + 1][x] != '1'
// 		|| data->map[y][x - 1] != '1' || data->map[y][x + 1] != '1')
// 		return (error_exit("Error: Door must be surrounded by walls"), 0);
// 	return (1);
// }

int	validate_doors(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(data->map[y]))
		{
			if (data->map[y][x] == 'D')
			{
				if (!check_player_surroundings(data, y, x))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
