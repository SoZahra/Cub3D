/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:48:36 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/21 19:37:35 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// void	print_map_state(t_data *data, char *message)
// {
// 	printf("=== %s ===\n", message);
// 	for (int y = 0; y < data->map_height; y++)
// 	{
// 		printf("Line %2d: [", y);
// 		for (int x = 0; x < data->map_width; x++)
// 		{
// 			printf("%c", data->copie_map[y][x]);
// 		}
// 		printf("]\n");
// 	}
// 	printf("\n===================\n");
// }

int	is_border_valid(t_data *data, int y, int x)
{
	int	line_len;

	line_len = ft_strlen(data->map[y]);
	if (x >= line_len)
	{
		if (x == line_len && line_len > 0 && data->map[y][line_len - 1] == '1')
			return (1);
		return (0);
	}
	if (data->map[y][x] == '1')
		return (1);
	if (data->map[y][x] == ' ')
		return (is_space_closed(data, y, x));
	return (0);
}

static int	check_zero_surroundings(t_data *data, int y, int x)
{
	if (data->map[y][x] != '0')
		return (1);
	if (y == data->map_height - 1 || y == 0 || x == 0
		|| x == (int)ft_strlen(data->map[y]) - 1)
		return (error_exit("Error: Zero on map border"), 0);
	if (data->map[y - 1][x] == ' ' || data->map[y + 1][x] == ' '
		|| data->map[y][x - 1] == ' ' || data->map[y][x + 1] == ' ')
		return (error_exit("Error: Zero not properly surrounded"), 0);
	return (1);
}

int	check_zeros(t_data *data)
{
	int	y;
	int	x;
	int	line_len;

	y = 0;
	while (y < data->map_height)
	{
		line_len = ft_strlen(data->map[y]);
		x = 0;
		while (x < line_len)
		{
			if (data->map[y][x] == '0')
			{
				if (y == data->map_height - 1 || y == 0 || x == 0
					|| x == line_len - 1)
					return (error_exit("Error: Zero on map border"), 0);
				if (!check_zero_surroundings(data, y, x))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_valid_characters(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (!is_map_char(data->map[y][x]))
				return (error_exit("Error: Map invalid"), 0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_map_valid(t_data *data)
{
	int	y;
	int	x;

	y = ((x = 0));
	if (!check_valid_characters(data))
		return (0);
	if (!check_map_borders(data))
		return (0);
	while (y < data->map_height)
	{
		while (x < data->map_width)
		{
			if (!is_space_closed(data, y, x))
				return (error_exit("Error: Map has unclosed spaces"), 0);
			x++;
		}
		y++;
	}
	if (!check_zeros(data))
		return (0);
	if (!check_player(data))
		return (0);
	return (1);
}
