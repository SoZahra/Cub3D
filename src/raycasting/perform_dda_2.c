/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:47:25 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/20 16:48:57 by fzayani          ###   ########.fr       */
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
	if (ray->map_x < 0 || ray->map_x >= data->map_width
		|| ray->map_y < 0 || ray->map_y >= data->map_height
		|| data->map[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}
