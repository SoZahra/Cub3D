/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:51:36 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/15 15:27:43 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	perform_dda(t_ray *ray, t_data *data)
{
	ray->hit = 0;
	while (ray->hit == 0)
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
		if (ray->map_x < 0 || ray->map_x >= data->map_width || ray->map_y < 0
			|| ray->map_y >= data->map_height
			|| data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
		if (data->map[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
        else if (data->map[ray->map_y][ray->map_x] == 'D')
        {
            for (int i = 0; i < data->num_doors; i++)
            {
                if (data->doors[i].x == ray->map_x &&
                    data->doors[i].y == ray->map_y)
                {
                    if (!data->doors[i].is_open)
                        ray->hit = 2;
                    break;
                }
            }
        }
	}
}

// void calculate_wall_dist(t_ray *ray)
// {
//     if (ray->side == 0)
//         ray->wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
//     else
//         ray->wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
// }

void calculate_wall_dist(t_ray *ray)
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
