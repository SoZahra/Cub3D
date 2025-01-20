/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:36:55 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/20 15:43:33 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	set_image_properties(t_data *data, int bpp, int len, int endian)
{
	data->img.bits_per_pixel = bpp;
	data->img.line_length = len;
	data->img.endian = endian;
	data->img.width = WIN_WIDTH;
	data->img.height = WIN_HEIGHT;
}

int	init_image_addr(t_data *data)
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

int	init_mlx_window(t_data *data)
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
