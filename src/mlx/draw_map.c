/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:34:09 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/13 14:35:36 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	draw_background(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, data->c_color);
			x++;
		}
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, data->f_color);
			x++;
		}
		y++;
	}
}

int	render(t_data *data)
{
	draw_background(data);
	return (0);
}