/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:16:17 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/10 14:56:58 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	find_last_non_space(t_data *data, int y)
{
	int	last_char_index;

	last_char_index = data->map_width - 1;
	while (last_char_index >= 0 && data->map[y][last_char_index] == ' ')
		last_char_index--;
	return (last_char_index);
}

static int	check_adjacent_cells(t_data *data, int y, int x)
{
	int	up;
	int	down;
	int	left;
	int	right;

	up = y - 1;
	down = y + 1;
	left = x - 1;
	right = x + 1;
	if (up < 0 || down >= data->map_height || left < 0
		|| right >= data->map_width)
		return (0);
	if ((data->map[up][x] != '1' && data->map[up][x] != ' ')
		|| (data->map[down][x] != '1' && data->map[down][x] != ' ')
		|| (data->map[y][left] != '1' && data->map[y][left] != ' ')
		|| (data->map[y][right] != '1' && data->map[y][right] != ' '))
		return (0);
	return (1);
}

int	is_space_closed(t_data *data, int y, int x)
{
	int	last_char_index;

	if (data->map[y][x] != ' ')
		return (1);
	if (is_space_at_beginning(data, y, x))
		return (1);
	if (check_space_sequence(data, y, x))
		return (1);
	printf("DEBUG: Checking space at y:%d, x:%d\n", y, x);
	last_char_index = find_last_non_space(data, y);
	if (x > last_char_index)
		return (1);
	return (check_adjacent_cells(data, y, x));
}

int	find_map_start(char **lines)
{
	int	i;
	int	f_elements;
	int	ret;

	i = 0;
	f_elements = 0;
	while (lines[i])
	{
		ret = process_line(lines, &i, &f_elements);
		if (ret >= 0 || ret == -1)
			return (ret);
		i++;
	}
	return (-1);
}

int	get_map_dimensions(char **lines, int start_line, int *height, int *width)
{
	int	i;
	int	max_width;
	int	current_width;

	i = start_line;
	max_width = 0;
	*height = 0;
	while (lines[i])
	{
		current_width = ft_strlen(lines[i]);
		if (current_width > max_width)
			max_width = current_width;
		(*height)++;
		i++;
	}
	*width = max_width;
	return (1);
}
