/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:56:03 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/22 12:14:23 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	game_loop(t_data *data)
{
	if (!data || !data->mlx.mlx || !data->mlx.win || !data->img.img
		|| !data->img.addr)
		return (0);
	ft_memset(data->img.addr, 0, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
	handle_rotation(data);
	handle_forward_movement(data);
	handle_strafe_movement(data);
	handle_door(data);
	update_doors(data);
	update_wall_animation(data);
	raycasting(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->img.img, 0, 0);
	return (0);
}

// t_texture	*select_texture(t_data *data, t_ray *ray)
// {
// 	int	frame_index;

// 	if (ray->hit == 1)
// 	{
// 		frame_index = (int)data->wall_tex.animation_time;
// 		return (&data->wall_tex.frames[frame_index]);
// 	}
// 	if (ray->hit == 2)
// 		return (&data->mlx.do_tex);
// 	if (ray->side == 0)
// 	{
// 		if (ray->ray_dir_x > 0)
// 			return (&data->mlx.ea_tex);
// 		return (&data->mlx.we_tex);
// 	}
// 	if (ray->ray_dir_y > 0)
// 		return (&data->mlx.so_tex);
// 	return (&data->mlx.no_tex);
// }

t_texture	*select_texture(t_data *data, t_ray *ray)
{
	int	frame_index;

	if (ray->hit == 2)
		return (&data->mlx.do_tex);
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&data->mlx.ea_tex);
		return (&data->mlx.we_tex);
	}
	if (ray->ray_dir_y > 0)
	{
		frame_index = (int)data->wall_tex.animation_time;
		return (&data->wall_tex.frames[frame_index]);
	}
	return (&data->mlx.no_tex);
}

int	apply_lighting(int color, double distance)
{
	int		r;
	int		g;
	int		b;
	double	intensity;
	double	max_distance;

	max_distance = 5.0;
	intensity = 1.0 - (distance / max_distance);
	if (intensity < 0.1)
		intensity = 0.1;
	r = ((color >> 16) & 0xFF) * intensity;
	g = ((color >> 8) & 0xFF) * intensity;
	b = (color & 0xFF) * intensity;
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

int	get_texture_color(t_data *data, t_ray *ray, int y)
{
	t_texture	*texture;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			color;

	texture = select_texture(data, ray);
	if (!texture || !texture->addr)
		return (0);
	get_wall_x(ray, &wall_x);
	tex_x = get_tex_x_(ray, texture, wall_x);
	tex_y = get_tex_y_(ray, texture, y);
	color = texture->addr[tex_y * texture->width + tex_x];
	color = apply_lighting(color, ray->wall_dist);
	return (color);
}

void	raycasting(t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray.pos_x = data->player.pos_x;
	ray.pos_y = data->player.pos_y;
	ray.dir_x = data->player.dir_x;
	ray.dir_y = data->player.dir_y;
	ray.plane_x = data->player.plane_x;
	ray.plane_y = data->player.plane_y;
	while (x < WIN_WIDTH)
	{
		init_ray_dir(&ray, data, x);
		init_ray_dist(&ray);
		init_ray_step(&ray);
		perform_dda(&ray, data);
		calculate_wall_dist(&ray);
		calculate_line_height(&ray);
		draw_vertical_line(data, &ray, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->img.img, 0, 0);
}
