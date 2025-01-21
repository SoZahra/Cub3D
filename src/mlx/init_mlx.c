/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:41:34 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/21 20:41:01 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
		return (error_exit("Failed to load EA texture"), 0);
	if (!load_wall_textures(data))
		return (error_exit("Failed to load wall textures"), 0);
	if (data->c_is_texture)
	{
		if (!load_texture(data, &data->sky_tex, data->c_texture))
			return (error_exit("Failed to load SKY texture"), 0);
	}
	if (data->f_is_texture)
	{
		if (!load_texture(data, &data->floor, data->f_texture))
			return (error_exit("Failed to load FLOOR texture"), 0);
	}
	return (1);
}
