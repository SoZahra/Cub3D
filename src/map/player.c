/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:22:42 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/14 12:20:19 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// static int	check_line_for_player(char *line, int y, t_data *data, int *count)
// {
// 	int	x;
// 	int	len;

// 	x = 0;
// 	len = ft_strlen(line);
// 	while (x < len)
// 	{
// 		if (ft_strchr("NSEW", line[x]))
// 		{
// 			(*count)++;
// 			data->player.pos_x = x;
// 			data->player.pos_y = y;
// 			data->player.player_dir = line[x];
// 		}
// 		x++;
// 	}
// 	return (1);
// }

//fonctionne
// int	check_player(t_data *data)
// {
// 	int	y;
// 	int	player_count;

// 	y = 0;
// 	player_count = 0;
// 	while (y < data->map_height)
// 	{
// 		check_line_for_player(data->map[y], y, &player_count);
// 		y++;
// 	}
// 	if (player_count != 1)
// 	{
// 		// printf("DEBUG: Found %d players\n", player_count);
// 		return (error_exit("Error: Must have exactly one player"), 0);
// 	}
// 	return (1);
// }

// int	check_player(t_data *data)
// {
// 	int		y;
// 	int		player_count;
// 	t_ray	ray;

// 	y = 0;
// 	player_count = 0;
// 	while (y < data->map_height)
// 	{
// 		check_line_for_player(data->map[y], y, data, &player_count);
// 		y++;
// 	}
// 	if (player_count != 1)
// 		return (error_exit("Error: Must have exactly one player"), 0);
// 	init_player_pos(&ray, data);
// 	return (1);
// }

static int    check_line_for_player(char *line, int y, t_data *data, int *count)
{
    int    x;
    int    len;

    x = 0;
    len = ft_strlen(line);
    while (x < len)
    {
        // printf("DEBUG: Checking char at y:%d, x:%d: '%c'\n", y, x, line[x]);
        if (ft_strchr("NSEW", line[x]))
        {
            // printf("DEBUG: Found player at y:%d, x:%d: '%c'\n", y, x, line[x]);
            (*count)++;
            // printf("DEBUG: Player count now: %d\n", *count);
            data->player.pos_x = x;
            data->player.pos_y = y;
            data->player.player_dir = line[x];
        }
        x++;
    }
    return (1);
}

int    check_player(t_data *data)
{
    int        y;
    int        player_count;
    t_ray    ray;

    y = 0;
    player_count = 0;
    // printf("\nDEBUG: Starting player check\n");
    // printf("DEBUG: Map height: %d\n", data->map_height);

    while (y < data->map_height)
    {
        // printf("\nDEBUG: Checking line %d: [%s]\n", y, data->map[y]);
        check_line_for_player(data->map[y], y, data, &player_count);
        y++;
    }

    // printf("DEBUG: Final player count: %d\n\n", player_count);

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
