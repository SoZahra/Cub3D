/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:56:03 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/16 11:33:24 by fzayani          ###   ########.fr       */
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
	raycasting(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->img.img, 0, 0);
	return (0);
}

static void	init_ray_position(t_ray *ray, t_data *data)
{
	if (!ray || !data)
		return ;
	ray->pos_x = (double)data->player.pos_x + 0.5;
	ray->pos_y = (double)data->player.pos_y + 0.5;
}

static void	set_direction_north(t_ray *ray)
{
	ray->dir_x = 0;
	ray->dir_y = -1;
	ray->plane_x = 0.66;
	ray->plane_y = 0;
}

static void	set_direction_vectors_(t_ray *ray, char dir)
{
	if (dir == 'N')
		set_direction_north(ray);
	else if (dir == 'S')
	{
		ray->dir_x = 0;
		ray->dir_y = 1;
		ray->plane_x = -0.66;
		ray->plane_y = 0;
	}
	else if (dir == 'E')
	{
		ray->dir_x = 1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		ray->dir_x = -1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = -0.66;
	}
}

static void	update_player_vectors(t_ray *ray, t_data *data)
{
	data->player.dir_x = ray->dir_x;
	data->player.dir_y = ray->dir_y;
	data->player.plane_x = ray->plane_x;
	data->player.plane_y = ray->plane_y;
}

static void	init_movement_values(t_data *data)
{
	data->movement.move_speed = 0.1;
	data->movement.rot_speed = 0.05;
	data->movement.forward = 0;
	data->movement.backward = 0;
	data->movement.left = 0;
	data->movement.right = 0;
	data->movement.rot_left = 0;
	data->movement.rot_right = 0;
}

void	init_player_pos(t_ray *ray, t_data *data)
{
	if (!ray || !data)
		return ;
	init_ray_position(ray, data);
	set_direction_vectors_(ray, data->player.player_dir);
	update_player_vectors(ray, data);
	init_movement_values(data);
}

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

static t_texture	*select_texture(t_data *data, t_ray *ray)
{
	if (ray->hit == 2)
		return (&data->mlx.do_tex);
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&data->mlx.ea_tex);
		return (&data->mlx.we_tex);
	}
	if (ray->ray_dir_y > 0)
		return (&data->mlx.so_tex);
	return (&data->mlx.no_tex);
}

int	get_tex_color(t_texture *texture, int tex_x, int tex_y)
{
	if (tex_x < 0 || tex_x >= texture->width || tex_y < 0
		|| tex_y >= texture->height)
		return (0);
	return (texture->addr[tex_y * (texture->line_length / 4) + tex_x]);
}

static int	get_wall_x(t_ray *ray, double *wall_x)
{
	if (ray->side == 0)
		*wall_x = ray->pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		*wall_x = ray->pos_x + ray->wall_dist * ray->ray_dir_x;
	*wall_x -= floor(*wall_x);
	return (1);
}

static int	get_tex_x_(t_ray *ray, t_texture *texture, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

static int	get_tex_y_(t_ray *ray, t_texture *texture, int y)
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

int	get_texture_color(t_data *data, t_ray *ray, int y)
{
	t_texture	*texture;
	double		wall_x;
	int			tex_x;
	int			tex_y;

	texture = select_texture(data, ray);
	if (!texture || !texture->addr)
		return (0);
	get_wall_x(ray, &wall_x);
	tex_x = get_tex_x_(ray, texture, wall_x);
	tex_y = get_tex_y_(ray, texture, y);
	return (texture->addr[tex_y * texture->width + tex_x]);
}

static void	draw_sky(t_data *data, t_ray *ray, int x, int y)
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
		tex_x = (int)((x + rot * WIN_WIDTH / (2 * M_PI)) * data->sky_tex.width
				/ WIN_WIDTH) % data->sky_tex.width;
		tex_y = (int)(y * data->sky_tex.height / (WIN_HEIGHT / 2))
			% data->sky_tex.height;
		data->img.addr[y * WIN_WIDTH + x] = get_tex_color(&data->sky_tex, tex_x,
				tex_y);
	}
	else
		data->img.addr[y * WIN_WIDTH + x] = data->c_color;
}

static void	draw_floor(t_data *data, int x, int y)
{
	if ((y * WIN_WIDTH + x) < (WIN_WIDTH * WIN_HEIGHT))
		data->img.addr[y * WIN_WIDTH + x] = data->f_color;
}

static void	draw_wall(t_data *data, t_ray *ray, int x, int y)
{
	if ((y * WIN_WIDTH + x) < (WIN_WIDTH * WIN_HEIGHT))
		data->img.addr[y * WIN_WIDTH + x] = get_texture_color(data, ray, y);
}

static void	draw_section(t_data *data, t_ray *ray, t_draw_section *ds)
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
