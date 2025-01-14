/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:06:21 by lizzieanani       #+#    #+#             */
/*   Updated: 2025/01/14 13:32:24 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	is_surrounded(char **map, int x, int y, int height)
{
	int	width;

	width = ft_strlen(map[y]);
	if (x == 0 || y == 0 || y == height - 1 || x == width - 1)
		return (0);
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' || map[y][x - 1] == ' '
		|| map[y][x + 1] == ' ')
		return (0);
	return (1);
}

static int	check_map_closure(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '0' || is_valid_player_char(data->map[y][x]))
			{
				if (!is_surrounded(data->map, x, y, data->map_height))
					return (error_exit("Map non fermée"), 1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

// static int	validate_player_position(t_data *data)
// {
// 	int	player_count;
// 	int	x;
// 	int	y;

// 	player_count = 0;
// 	y = 0;
// 	while (y < data->map_height)
// 	{
// 		x = 0;
// 		while (data->map[y][x])
// 		{
// 			if (is_valid_player_char(data->map[y][x]))
// 			{
// 				player_count++;
// 				data->player.pos_x = x;
// 				data->player.pos_y = y;
// 				data->player.player_dir = data->map[y][x];
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	if (player_count != 1)
// 		return (error_msg("Il doit y avoir exactement une position de départ"));
// 	return (0);
// }

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '\n' || c == 'D');
}

int	is_valid_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	validate_player_position(t_data *data)
{
	int	player_count;
	int	x;
	int	y;

	player_count = 0;
	y = 0;
	printf("Checking for player position in map with height: %d\n",
		data->map_height);
	while (y < data->map_height)
	{
		x = 0;
		printf("Checking line %d: '%s'\n", y, data->map[y]);
		while (data->map[y][x])
		{
			if (is_valid_player_char(data->map[y][x]))
			{
				printf("Found player '%c' at position [%d][%d]\n",
					data->map[y][x], y, x);
				player_count++;
				data->player.pos_x = x;
				data->player.pos_y = y;
				data->player.player_dir = data->map[y][x];
			}
			x++;
		}
		y++;
	}
	printf("Total players found: %d\n", player_count);
	if (player_count != 1)
		return (error_exit("Il doit y avoir exactement une position de départ"), 1);
	return (0);
}

// static int	validate_map_chars(char **map, int height)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < height)
// 	{
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			if (!is_valid_map_char(map[y][x]))
// 				return (error_msg("Caractère invalide dans la map"));
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (0);
// }

static int	validate_map_chars(char **map, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x])
		{
			printf("Checking char '%c' at position [%d][%d]\n", map[y][x], y,
				x);
			if (!is_valid_map_char(map[y][x]))
			{
				printf("Invalid char '%c' found at [%d][%d]\n", map[y][x], y,
					x);
				return (error_exit("Caractère invalide dans la map"), 1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_map(t_data *data)
{
	if (!data->map || !data->map_height)
		return (error_exit("Map manquante"), 1);
	if (validate_map_chars(data->map, data->map_height))
		return (1);
	if (validate_player_position(data))
		return (1);
	if (check_map_closure(data))
		return (1);
	return (0);
}
