/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lizzieananifoli <lizzieananifoli@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:18:45 by lanani-f          #+#    #+#             */
/*   Updated: 2025/01/04 01:23:35 by lizzieanani      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	set_direction_ns(t_ray *ray, char dir)
{
	if (dir == 'N')
	{
		ray->dir_x = 0;
		ray->dir_y = -1;
		ray->plane_x = 0.66;
		ray->plane_y = 0;
	}
	if (dir == 'S')
	{
		ray->dir_x = 0;
		ray->dir_y = 1;
		ray->plane_x = -0.66;
		ray->plane_y = 0;
	}
}

static void	set_direction_ew(t_ray *ray, char dir)
{
	if (dir == 'E')
	{
		ray->dir_x = 1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = 0.66;
	}
	if (dir == 'W')
	{
		ray->dir_x = -1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = -0.66;
	}
}

void	set_direction_vectors(t_ray *ray, char dir)
{
	set_direction_ns(ray, dir);
	set_direction_ew(ray, dir);
}
