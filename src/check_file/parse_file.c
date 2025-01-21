/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:11:44 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/21 17:03:06 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	validate_str_chars(const char *str)
{
	int	i;
	int	comma_count;
	int	had_digit;

	i = ((comma_count = had_digit = 0));
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			had_digit = 1;
		else if (str[i] == ',' && is_valid_comma_sequence(str, i, had_digit))
		{
			comma_count++;
			had_digit = 0;
		}
		else if (!is_valid_format(str, i, had_digit))
			return (0);
		i++;
	}
	return (comma_count == 2 && had_digit);
}

static int	extract_rgb_values(char **components, int *r, int *g, int *b)
{
	if (ft_arraylen(components) != 3)
		return (0);
	*r = ft_atoi(components[0]);
	*g = ft_atoi(components[1]);
	*b = ft_atoi(components[2]);
	return (1);
}

int	parse_color(const char *str)
{
	char	**components;
	char	*trimmed_str;
	int		r;
	int		g;
	int		b;

	trimmed_str = ft_strtrim2(str);
	if (!trimmed_str || !validate_str_chars(str))
		return (free(trimmed_str), -1);
	if (!validate_color_values(trimmed_str))
		return (free(trimmed_str), -1);
	components = ft_split(trimmed_str, ',');
	free(trimmed_str);
	if (!extract_rgb_values(components, &r, &g, &b))
		return (ft_free_split(components), -1);
	ft_free_split(components);
	return ((r << 16) | (g << 8) | b);
}

int	check_texture_format(const char *path)
{
	char	**parts;
	int		result;

	parts = ft_split(path, ' ');
	result = (ft_arraylen(parts) == 1);
	ft_free_split(parts);
	return (result);
}

int	parse_texture_colors(t_data *data, char **lines, const char *filename)
{
	int	i;
	int	map_start;

	(void)filename;
	i = 0;
	if (!data || !lines)
		return (-1);
	while (lines[i])
	{
		if (!parse_texture_line(data, lines[i]))
			return (-1);
		i++;
	}
	if (!data->no_loaded || !data->so_loaded || !data->we_loaded
		|| !data->ea_loaded || !data->f_loaded || !data->c_loaded
		|| !data->do_loaded)
		return (error_exit("Error: Missing required elements"), -1);
	map_start = find_map_start(lines);
	if (map_start == -1)
		return (error_exit("Error: map format or missing elements"), -1);
	if (!store_map(data, lines, map_start))
		return (error_exit("Error: Failed to store map"), -1);
	if (!check_map_valid(data))
		return (-1);
	return (1);
}
