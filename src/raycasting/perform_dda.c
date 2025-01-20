/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:51:36 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/20 16:48:04 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	check_door(t_ray *ray, t_data *data)
{
	int	i;

	i = 0;
	if (!data->doors)
		return (0);
	while (i < data->num_doors)
	{
		if (data->doors[i].x == ray->map_x
			&& data->doors[i].y == ray->map_y)
		{
			if (!data->doors[i].is_open)
				return (2);
			break ;
		}
		i++;
	}
	return (0);
}

static int	check_collision(t_ray *ray, t_data *data)
{
	if (check_wall_collision(ray, data))
		return (1);
	if (data->map[ray->map_y][ray->map_x] == 'D' && data->doors)
		return (check_door(ray, data));
	return (0);
}

void	perform_dda(t_ray *ray, t_data *data)
{
	int	hit_type;

	ray->hit = 0;
	while (ray->hit == 0)
	{
		update_ray_position(ray);
		hit_type = check_collision(ray, data);
		if (hit_type)
			ray->hit = hit_type;
	}
}

void	calculate_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	}
	else
	{
		ray->wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	}
	if (ray->wall_dist < 0)
		ray->wall_dist = 0;
}

void	calculate_line_height(t_ray *ray)
{
	ray->line_height = (int)(WIN_HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}
