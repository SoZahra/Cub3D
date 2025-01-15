/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:41:34 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/15 18:27:01 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->f_color = -1;
	data->c_color = -1;
	data->movement.move_speed = 0.1;
	data->movement.rot_speed = 0.05;
}

void	init_minimap(t_data *data)
{
	int	max_dim;

	max_dim = data->map_width;
	if (data->map_height > max_dim)
		max_dim = data->map_height;
	data->minimap.scale = MINIMAP_SIZE / max_dim;
	if (data->minimap.scale < 2)
		data->minimap.scale = 2;
	data->minimap.width = data->map_width * data->minimap.scale;
	data->minimap.height = data->map_height * data->minimap.scale;
	data->minimap.offset_x = 10;
	data->minimap.offset_y = WIN_HEIGHT - data->minimap.height - 10;
}

int	init_game(t_data *data)
{
	t_ray	initial_ray;

	if (!init_mlx(data))
		return (0);
	if (!check_player(data))
	{
		cleanup_mlx(data);
		return (0);
	}
	if (!load_textures(data))
	{
		cleanup_mlx(data);
		return (0);
	}
	if (!init_doors(data))
	{
		cleanup_mlx(data);
		return (0);
	}
	init_minimap(data);
	init_player_pos(&initial_ray, data);
	init_hooks(data);
	raycasting(data);
	return (1);
}

static int	init_mlx_window(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		return (error_exit("Failed to init MLX"), 0);
	data->mlx.win = mlx_new_window(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT,
			"Cub3D");
	if (!data->mlx.win)
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
		return (error_exit("Failed to create window"), 0);
	}
	return (1);
}

static int	create_mlx_image(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img.img)
	{
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
		return (error_exit("Failed to create image"), 0);
	}
	return (1);
}

static void	set_image_properties(t_data *data, int bpp, int len, int endian)
{
	data->img.bits_per_pixel = bpp;
	data->img.line_length = len;
	data->img.endian = endian;
	data->img.width = WIN_WIDTH;
	data->img.height = WIN_HEIGHT;
}

static int	init_image_addr(t_data *data)
{
	int	bits_per_pixel;
	int	line_length;
	int	endian;

	data->img.addr = (int *)mlx_get_data_addr(data->img.img, &bits_per_pixel,
			&line_length, &endian);
	if (!data->img.addr)
	{
		mlx_destroy_image(data->mlx.mlx, data->img.img);
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
		return (error_exit("Failed to get image address"), 0);
	}
	set_image_properties(data, bits_per_pixel, line_length, endian);
	return (1);
}

int	init_mlx(t_data *data)
{
	if (!data)
		return (0);
	if (!init_mlx_window(data))
		return (0);
	if (!create_mlx_image(data))
		return (0);
	if (!init_image_addr(data))
		return (0);
	return (1);
}

void	check_textures_loaded(t_data *data)
{
	if (!data->mlx.no_tex.img || !data->mlx.so_tex.img || !data->mlx.we_tex.img
		|| !data->mlx.ea_tex.img)
	{
		cleanup_mlx(data);
		error_exit("Failed to load textures");
	}
}

int	load_texture(t_data *data, t_texture *tex, char *path)
{
	if (!path || !tex)
		return (0);
	tex->img = mlx_xpm_file_to_image(data->mlx.mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
		return (0);
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	if (!tex->addr)
	{
		mlx_destroy_image(data->mlx.mlx, tex->img);
		tex->img = NULL;
		return (0);
	}
	if (tex->width <= 0 || tex->height <= 0)
	{
		mlx_destroy_image(data->mlx.mlx, tex->img);
		tex->img = NULL;
		return (0);
	}
	return (1);
}

int	load_textures(t_data *data)
{
	if (!load_texture(data, &data->mlx.no_tex, data->no_texture))
		return (error_exit("Failed to load NO texture"), 0);
	if (!load_texture(data, &data->mlx.so_tex, data->so_texture))
		return (error_exit("Failed to load SO texture"), 0);
	if (!load_texture(data, &data->mlx.we_tex, data->we_texture))
		return (error_exit("Failed to load WE texture"), 0);
	if (!load_texture(data, &data->mlx.ea_tex, data->ea_texture))
		return (error_exit("Failed to load EA texture"), 0);
	if (!load_texture(data, &data->mlx.do_tex, data->do_texture))
		return (error_exit("Failed to load DO texture"), 0);
	if (data->c_is_texture && !load_texture(data, &data->sky_tex,
			data->c_texture))
		return (error_exit("Failed to load SKY texture"), 0);
	return (1);
}
