/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:56:03 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/15 10:43:44 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int game_loop(t_data *data)
{
    if (!data || !data->mlx.mlx || !data->mlx.win || !data->img.img || !data->img.addr)
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

void init_player_pos(t_ray *ray, t_data *data)
{
    // Position
    ray->pos_x = (double)data->player.pos_x + 0.5;
    ray->pos_y = (double)data->player.pos_y + 0.5;

    if (data->player.player_dir == 'N')
    {
        ray->dir_x = 0;
        ray->dir_y = -1;
        ray->plane_x = 0.66;
        ray->plane_y = 0;
    }
    else if (data->player.player_dir == 'S')
    {
        ray->dir_x = 0;
        ray->dir_y = 1;
        ray->plane_x = -0.66;
        ray->plane_y = 0;
    }
    else if (data->player.player_dir == 'E')
    {
        ray->dir_x = 1;
        ray->dir_y = 0;
        ray->plane_x = 0;
        ray->plane_y = 0.66;
    }
    else if (data->player.player_dir == 'W')
    {
        ray->dir_x = -1;
        ray->dir_y = 0;
        ray->plane_x = 0;
        ray->plane_y = -0.66;
    }
    data->player.dir_x = ray->dir_x;
    data->player.dir_y = ray->dir_y;
    data->player.plane_x = ray->plane_x;
    data->player.plane_y = ray->plane_y;

    data->movement.move_speed = 0.1;
    data->movement.rot_speed = 0.05;

    data->movement.forward = 0;
    data->movement.backward = 0;
    data->movement.left = 0;
    data->movement.right = 0;
    data->movement.rot_left = 0;
    data->movement.rot_right = 0;

    // Debug print pour vérifier l'initialisation
    // printf("Initial Direction: (%f, %f)\n", ray->dir_x, ray->dir_y);
    // printf("Initial Plane: (%f, %f)\n", ray->plane_x, ray->plane_y);
    // printf("Player Direction: %c\n", data->player.player_dir);
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
	tex_x = (int)(wall_x * texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}
static void	adjust_tex_y(int *tex_y, int tex_height)
{
	if (*tex_y < 0)
		*tex_y = 0;
	if (*tex_y >= tex_height)
		*tex_y = tex_height - 1;
}

static t_texture *select_texture(t_data *data, t_ray *ray)
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

int get_tex_color(t_texture *texture, int tex_x, int tex_y)
{
    if (tex_x < 0 || tex_x >= texture->width || tex_y < 0 || tex_y >= texture->height)
        return (0);
    return texture->addr[tex_y * (texture->line_length / 4) + tex_x];
}

int	get_texture_color(t_data *data, t_ray *ray, int y)
{
	int			tex_x;
	int			tex_y;
	t_texture	*texture;
	double		step;

	texture = select_texture(data, ray);
	if (!texture || !texture->addr)
        return (0);
	tex_x = get_tex_x(texture, ray);
	step = 1.0 * texture->height / ray->line_height;
	tex_y = (int)((y - ray->draw_start) * step);
	adjust_tex_y(&tex_y, texture->height);
	return (get_tex_color(texture, tex_x, tex_y));
}

void draw_vertical_line(t_data *data, t_ray *ray, int x)
{
    int y;

    if (!data || !data->img.addr)
        return;
    if (x < 0 || x >= WIN_WIDTH)
        return;
    y = 0;
    while (y < ray->draw_start && y < WIN_HEIGHT)
    {
        if ((y * WIN_WIDTH + x) < (WIN_WIDTH * WIN_HEIGHT))
            data->img.addr[y * WIN_WIDTH + x] = data->c_color;
        y++;
    }
    while (y < ray->draw_end && y < WIN_HEIGHT)
    {
        if ((y * WIN_WIDTH + x) < (WIN_WIDTH * WIN_HEIGHT))
            data->img.addr[y * WIN_WIDTH + x] = get_texture_color(data, ray, y);
        y++;
    }
    while (y < WIN_HEIGHT)
    {
        if ((y * WIN_WIDTH + x) < (WIN_WIDTH * WIN_HEIGHT))
            data->img.addr[y * WIN_WIDTH + x] = data->f_color;
        y++;
    }
}

void raycasting(t_data *data)
{
    t_ray   ray;
    int     x;

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

// void	raycasting(t_data *data)
// {
// 	t_ray	ray;
// 	int		x;

// 	x = 0;
// 	init_player_pos(&ray, data);
// 	while (x < WIN_WIDTH)
// 	{
// 		init_ray_dir(&ray, data, x);
// 		init_ray_dist(&ray);
// 		init_ray_step(&ray);
// 		perform_dda(&ray, data);
// 		calculate_wall_dist(&ray);
// 		calculate_line_height(&ray);
// 		draw_vertical_line(data, &ray, x);
// 		x++;
// 	}
// 	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->img.img, 0, 0);
// }
