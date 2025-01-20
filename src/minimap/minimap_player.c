/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:00:00 by lanani-f          #+#    #+#             */
/*   Updated: 2025/01/20 17:28:58 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	draw_player_on_map(t_data *data)
{
	int	player_x;
	int	player_y;
	int	dir_x;
	int	dir_y;

	player_x = (int)data->player.pos_x;
	player_y = (int)data->player.pos_y;
	put_minimap_pixel(data, player_x, player_y, 0xFF0000);
	dir_x = player_x + (int)(data->player.dir_x * 2);
	dir_y = player_y + (int)(data->player.dir_y * 2);
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
