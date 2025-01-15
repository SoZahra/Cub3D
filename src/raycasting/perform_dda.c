/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:51:36 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/15 18:30:52 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// void	perform_dda(t_ray *ray, t_data *data)
// {
// 	int	i;

// 	ray->hit = 0;
// 	while (ray->hit == 0)
// 	{
// 		if (ray->side_dist_x < ray->side_dist_y)
// 		{
// 			ray->side_dist_x += ray->delta_dist_x;
// 			ray->map_x += ray->step_x;
// 			ray->side = 0;
// 		}
// 		else
// 		{
// 			ray->side_dist_y += ray->delta_dist_y;
// 			ray->map_y += ray->step_y;
// 			ray->side = 1;
// 		}
// 		if (ray->map_x < 0 || ray->map_x >= data->map_width || ray->map_y < 0
// 			|| ray->map_y >= data->map_height
// 			|| data->map[ray->map_y][ray->map_x] == '1')
// 			ray->hit = 1;
// 		if (data->map[ray->map_y][ray->map_x] == '1')
// 			ray->hit = 1;
// 		else if (data->map[ray->map_y][ray->map_x] == 'D')
// 		{
// 			i = 0;
// 			while (i < data->num_doors)
// 			{
// 				if (data->doors[i].x == ray->map_x
// 					&& data->doors[i].y == ray->map_y)
// 				{
// 					if (!data->doors[i].is_open)
// 						ray->hit = 2;
// 					break ;
// 				}
// 				i++;
// 			}
// 		}
// 	}
// }

static void	update_ray_position(t_ray *ray)
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

static int	check_wall_collision(t_ray *ray, t_data *data)
{
	if (ray->map_x < 0 || ray->map_x >= data->map_width
		|| ray->map_y < 0 || ray->map_y >= data->map_height
		|| data->map[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

static int	check_door(t_ray *ray, t_data *data)
{
	int	i;

	i = 0;
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
	if (data->map[ray->map_y][ray->map_x] == 'D')
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
