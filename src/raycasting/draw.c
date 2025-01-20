/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:12:21 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/20 17:13:56 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	draw_vertical_line(t_data *data, t_ray *ray, int x)
{
	t_draw_section	ds;
	int				section_height;

	if (!data || !data->img.addr)
		return ;
	if (x < 0 || x >= WIN_WIDTH)
		return ;
	section_height = WIN_HEIGHT / 3;
	ds.x = x;
	ds.start = 0;
	ds.end = section_height;
	draw_section(data, ray, &ds);
	ds.start = section_height;
	ds.end = section_height * 2;
	draw_section(data, ray, &ds);
	ds.start = section_height * 2;
	ds.end = WIN_HEIGHT;
	draw_section(data, ray, &ds);
}

void	draw_sky(t_data *data, t_ray *ray, int x, int y)
{
	double	rot;
	int		tex_x;
	int		tex_y;

	(void)ray;
	if ((y * WIN_WIDTH + x) >= (WIN_WIDTH * WIN_HEIGHT))
		return ;
	if (data->c_is_texture)
	{
		rot = atan2(data->player.dir_y, data->player.dir_x);
		rot = fmod(rot + 2 * M_PI, 2 * M_PI);
		tex_x = (int)(((float)x / WIN_WIDTH + rot / (2 * M_PI))
				* data->sky_tex.width);
		tex_x = ((tex_x % data->sky_tex.width) + data->sky_tex.width)
			% data->sky_tex.width;
		tex_y = (int)((float)y / (WIN_HEIGHT / 2) * data->sky_tex.height);
		tex_y = ((tex_y % data->sky_tex.height) + data->sky_tex.height)
			% data->sky_tex.height;
		data->img.addr[y * WIN_WIDTH + x] = get_tex_color(&data->sky_tex, tex_x,
				tex_y);
	}
	else
		data->img.addr[y * WIN_WIDTH + x] = data->c_color;
}

void	draw_wall(t_data *data, t_ray *ray, int x, int y)
{
	if ((y * WIN_WIDTH + x) < (WIN_WIDTH * WIN_HEIGHT))
		data->img.addr[y * WIN_WIDTH + x] = get_texture_color(data, ray, y);
}

void	draw_section(t_data *data, t_ray *ray, t_draw_section *ds)
{
	int	y;

	y = ds->start;
	while (y < ds->end && y < WIN_HEIGHT)
	{
		if (y < ray->draw_start)
			draw_sky(data, ray, ds->x, y);
		else if (y < ray->draw_end)
			draw_wall(data, ray, ds->x, y);
		else
			draw_floor(data, ds->x, y);
		y++;
	}
}
