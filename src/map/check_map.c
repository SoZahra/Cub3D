/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:58:38 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/21 17:44:41 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	find_last_wall(t_data *data, int y)
{
	int	last_char_index;
	int	line_len;

	line_len = ft_strlen(data->map[y]);
	last_char_index = line_len - 1;
	while (last_char_index >= 0 && data->map[y][last_char_index] == ' ')
		last_char_index--;
	return (last_char_index);
}

static int	check_border_line(t_data *data, int y)
{
	int	x;
	int	line_len;

	x = 0;
	line_len = ft_strlen(data->map[y]);
	while (x < line_len)
	{
		if (data->map[0][x] != '1' && data->map[0][x] != ' ')
			return (error_exit("Error: First map line not valid"), 0);
		x++;
	}
	return (1);
}

int	check_map_borders(t_data *data)
{
	int	y;
	int	last_wall;

	y = 0;
	while (y < data->map_height)
	{
		last_wall = find_last_wall(data, y);
		if (last_wall < 0 || data->map[y][last_wall] != '1')
			return (error_exit("Error: Map line does not end with a wall"), 0);
		if (y == 0 || y == data->map_height - 1)
			if (!check_border_line(data, y))
				return (0);
		y++;
	}
	return (1);
}

int	check_space_sequence(t_data *data, int y, int x)
{
	int	left;
	int	right;

	left = x - 1;
	right = x + 1;
	while (left >= 0 && (data->map[y][left] == ' '))
		left--;
	if (left >= 0 && data->map[y][left] == '1')
	{
		while (right < data->map_width && (data->map[y][right] == ' '))
			right++;
		if (right < data->map_width && data->map[y][right] == '1')
			return (1);
	}
	return (0);
}
