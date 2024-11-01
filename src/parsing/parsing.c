/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:11:22 by fzayani           #+#    #+#             */
/*   Updated: 2024/11/01 18:45:50 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	check_invalid_characters(t_data *data, char element)
{
	if (element != 'N' && element != 'S' && element != 'E' && element != 'W' && element != '1'
		&& element != '0')
	{
		free_map(data);
		error_exit("Error: map contains invalid characters.");
	}
}

void	count_map_elements(t_data *data, int *exit_count, int *start_count,
		int *collectible_count)
{
	int	i;
	int	j;

	i = ((j = 0));
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (data->map[i][j] == 'E')
				(*exit_count)++;
			else if (data->map[i][j] == 'P')
				(*start_count)++;
			else if (data->map[i][j] == 'C')
				(*collectible_count)++;
			check_invalid_characters(data, data->map[i][j]);
			j++;
		}
		i++;
	}
}

int	check_map_elements(t_data *data)
{
	int	exit_count;
	int	start_count;
	int	collectible_count;

	exit_count = ((start_count = collectible_count = 0));
	count_map_elements(data, &exit_count, &start_count, &collectible_count);
	// check_map_line_length(data);
	if (exit_count != 1 || start_count != 1 || collectible_count < 1)
		return (ft_printf("Error: Map need 1 exit, 1 collectible,\
				and 1 start position.\n"), 0);
	return (1);
}
