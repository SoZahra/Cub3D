/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:00:00 by lanani-f          #+#    #+#             */
/*   Updated: 2025/01/14 11:32:35 by fzayani          ###   ########.fr       */
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
	// put_minimap_pixel(data, dir_x, dir_y, 0xFF6666);
}
