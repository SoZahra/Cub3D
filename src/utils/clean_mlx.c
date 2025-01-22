/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:17:53 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/22 12:19:53 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	destroy_texture(void *mlx, t_texture *tex)
{
	if (!mlx || !tex || !tex->img)
		return ;
	mlx_destroy_image(mlx, tex->img);
	tex->img = NULL;
	tex->addr = NULL;
}

void	clean_wesh(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		destroy_texture(data->mlx.mlx, &data->wall_tex.frames[i]);
		i++;
	}
}

void	cleanup_mlx(t_data *data)
{
	if (!data->mlx.mlx)
		return ;
	if (data->img.img)
	{
		mlx_destroy_image(data->mlx.mlx, data->img.img);
		data->img.img = NULL;
		data->img.addr = NULL;
	}
	destroy_texture(data->mlx.mlx, &data->mlx.no_tex);
	destroy_texture(data->mlx.mlx, &data->mlx.so_tex);
	destroy_texture(data->mlx.mlx, &data->mlx.we_tex);
	destroy_texture(data->mlx.mlx, &data->mlx.ea_tex);
	destroy_texture(data->mlx.mlx, &data->mlx.do_tex);
	destroy_texture(data->mlx.mlx, &data->sky_tex);
	destroy_texture(data->mlx.mlx, &data->floor);
	clean_wesh(data);
	if (data->mlx.win)
	{
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		data->mlx.win = NULL;
	}
	mlx_destroy_display(data->mlx.mlx);
	free(data->mlx.mlx);
	data->mlx.mlx = NULL;
}
