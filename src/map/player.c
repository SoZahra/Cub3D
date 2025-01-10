/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:22:42 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/10 18:49:15 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	check_line_for_player(char *line, int y, int *count)
{
	(void)y;
	int	x;
	int	len;

	x = 0;
	len = ft_strlen(line);
	while (x < len)
	{
		// printf("DEBUG: Checking position y:%d, x:%d, char:'%c'\n", y, x,
		// 	line[x]);
		if (ft_strchr("NSEW", line[x]))
			(*count)++;
		x++;
	}
	return (1);
}

int	check_player(t_data *data)
{
	int	y;
	int	player_count;

	y = 0;
	player_count = 0;
	while (y < data->map_height)
	{
		check_line_for_player(data->map[y], y, &player_count);
		y++;
	}
	if (player_count != 1)
	{
		// printf("DEBUG: Found %d players\n", player_count);
		return (error_exit("Error: Must have exactly one player"), 0);
	}
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
