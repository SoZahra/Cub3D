/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:22:42 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/21 19:35:49 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	check_player_surroundings(t_data *data, int y, int x)
{
	if (y == 0 || x == 0 || y == data->map_height - 1
		|| x >= (int)ft_strlen(data->map[y]) - 1)
		return (error_exit("Error: Position invalid (at border)"), 0);
	if (data->map[y - 1][x] == ' ' || data->map[y + 1][x] == ' '
		|| data->map[y][x - 1] == ' ' || data->map[y][x + 1] == ' ')
		return (error_exit("Error: Not properly surrounded by walls"), 0);
	return (1);
}

static int	check_line_for_player(char *line, int y, t_data *data, int *count)
{
	int	x;
	int	len;

	x = 0;
	len = ft_strlen(line);
	while (x < len)
	{
		if (ft_strchr("NSEW", line[x]))
		{
			(*count)++;
			data->player.pos_x = x;
			data->player.pos_y = y;
			data->player.player_dir = line[x];
			if (!check_player_surroundings(data, y, x))
				return (0);
		}
		x++;
	}
	return (1);
}

int	check_player(t_data *data)
{
	int		y;
	int		player_count;
	t_ray	ray;

	y = 0;
	player_count = 0;
	while (y < data->map_height)
	{
		if (!check_line_for_player(data->map[y], y, data, &player_count))
			return (0);
		y++;
	}
	if (player_count != 1)
		return (error_exit("Error: Must have exactly one player"), 0);
	init_player_pos(&ray, data);
	return (1);
}

int	is_valid_map_line(char *line)
{
	int	found_valid_char;

	found_valid_char = 0;
	while (*line)
	{
		if (*line != ' ' && *line != '1' && *line != '0' && *line != 'N'
			&& *line != 'S' && *line != 'E' && *line != 'W' && *line != '\n')
			return (0);
		if (*line == '1' || *line == '0' || *line == 'N' || *line == 'S'
			|| *line == 'E' || *line == 'W')
			found_valid_char = 1;
		line++;
	}
	return (found_valid_char);
}
