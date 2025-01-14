/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 01:10:53 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/14 11:17:44 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	get_minimap_color(char map_char)
{
	if (map_char == '1')
		return (0x808080);
	if (map_char == '0')
		return (0x303030);
	if (map_char == ' ')
		return (0x000000);
	return (0x000000);
}

int	is_in_minimap_bounds(t_minimap *minimap, int x, int y)
{
	if (x < 0 || x >= minimap->width || y < 0 || y >= minimap->height)
		return (0);
	return (1);
}

void	clear_minimap(t_data *data, t_minimap *minimap)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < minimap->height)
	{
		j = 0;
		while (j < minimap->width)
		{
			x = j + minimap->offset_x;
			y = i + minimap->offset_y;
			if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
				data->img.addr[y * WIN_WIDTH + x] = 0x000000;
			j++;
		}
		i++;
	}
}
