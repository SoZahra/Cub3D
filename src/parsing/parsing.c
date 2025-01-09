/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:11:22 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/09 14:27:10 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// void	check_invalid_characters(t_data *data, char element)
// {
// 	if (element != 'N' && element != 'S' && element != 'E' && element != 'W' && element != '1'
// 		&& element != '0')
// 	{
// 		free_map(data);
// 		error_exit("Error: map contains invalid characters.");
// 	}
// }

// int	check_map_elements(t_data *data)
// {
// 	int	i;
// 	int	j;
// 	int	player_count;

// 	player_count = ((i = j = 0));
// 	while(i++ < data->map_height)
// 	{
// 		while(j++ < data->map_width)
// 		{
// 			if(data->map[i][j] == 'N' || data->map[i][j] == 'S' ||
// 				data->map[i][j] == 'E' || data->map[i][j] == 'W')
// 			{
// 				player_count++;
// 				data->player.player_x = j;
// 				data->player.player_y = i;
// 				data->player.player_dir = data->map[i][j];
// 			}
// 			else if(data->map[i][j] != '0' && data->map[i][j] != '1')
// 				return(printf("Error : Invalid character '%c' in map.\n", data->map[i][j]), 0);
// 		}
// 	}
// 	if(player_count != 1)
// 		return (printf("Error : Map contain exactly one sarting position(N, S, E, or W).\n"), 0);
// 	return(1);
// }
