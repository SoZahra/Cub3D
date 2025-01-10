/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:01:57 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/10 15:05:59 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	get_map_width(char **lines, int start_line, int height)
{
	int	i;
	int	width;
	int	len;

	i = 0;
	width = 0;
	while (i < height)
	{
		len = get_adjusted_len(lines[start_line + i]);
		if (len > width)
			width = len;
		i++;
	}
	return (width);
}

static int	allocate_maps(t_data *data, int height, int width)
{
	int	i;

	data->map = malloc(sizeof(char *) * (height + 1));
	data->copie_map = malloc(sizeof(char *) * (height + 1));
	if (!data->map || !data->copie_map)
		return (0);
	i = 0;
	while (i < height)
	{
		data->map[i] = malloc(width + 1);
		data->copie_map[i] = malloc(width + 1);
		if (!data->map[i] || !data->copie_map[i])
			return (0);
		ft_memset(data->map[i], ' ', width);
		ft_memset(data->copie_map[i], ' ', width);
		data->map[i][width] = '\0';
		data->copie_map[i][width] = '\0';
		i++;
	}
	return (1);
}

static void	copy_line_content(t_data *data, char **lines, int start, int i)
{
	char	*src_line;
	int		line_len;

	src_line = lines[start + i];
	line_len = get_adjusted_len(src_line);
	if (line_len > 0)
	{
		ft_memcpy(data->map[i], src_line, line_len);
		ft_memcpy(data->copie_map[i], src_line, line_len);
	}
}

int	store_map(t_data *data, char **lines, int start_line)
{
	int	height;
	int	width;
	int	i;

	height = get_map_height(lines, start_line);
	width = get_map_width(lines, start_line, height);
	if (!allocate_maps(data, height, width))
		return (0);
	i = 0;
	while (i < height)
	{
		copy_line_content(data, lines, start_line, i);
		i++;
	}
	data->map[height] = NULL;
	data->copie_map[height] = NULL;
	data->map_height = height;
	data->map_width = width;
	return (1);
}
