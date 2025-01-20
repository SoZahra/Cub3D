/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:07:37 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/20 17:17:09 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	get_tex_x(t_texture *texture, t_ray *ray)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = ray->pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		wall_x = ray->pos_x + ray->wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

int	get_tex_color(t_texture *texture, int tex_x, int tex_y)
{
	if (tex_x < 0 || tex_x >= texture->width || tex_y < 0
		|| tex_y >= texture->height)
		return (0);
	return (texture->addr[tex_y * (texture->line_length / 4) + tex_x]);
}

int	get_wall_x(t_ray *ray, double *wall_x)
{
	if (ray->side == 0)
		*wall_x = ray->pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		*wall_x = ray->pos_x + ray->wall_dist * ray->ray_dir_x;
	*wall_x -= floor(*wall_x);
	return (1);
}

int	get_tex_x_(t_ray *ray, t_texture *texture, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * texture->width);
	if (ray->hit != 2)
	{
		if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
				&& ray->ray_dir_y < 0))
			tex_x = texture->width - tex_x - 1;
	}
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

int	get_tex_y_(t_ray *ray, t_texture *texture, int y)
{
	int		line_height;
	double	relative_y;
	double	tex_pos;
	int		tex_y;

	line_height = (int)((double)WIN_HEIGHT / ray->wall_dist);
	relative_y = y - (WIN_HEIGHT / 2 - line_height / 2);
	tex_pos = relative_y / (double)line_height;
	tex_y = (int)(tex_pos * texture->height);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	return (tex_y);
}
