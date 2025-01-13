/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:11:44 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/13 11:27:48 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	validate_str_chars(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isdigit(str[i]) || str[i] == ',' || str[i] == ' '))
		i++;
	if (str[i] != '\0' && str[i] != '\n')
		return (0);
	return (1);
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

int    parse_texture_colors(t_data *data, char **lines, const char *filename)
{
    int    i;

    // printf("\nDEBUG: Starting parse_texture_colors\n");
    (void)filename;
    if (!lines)
    {
        printf("DEBUG: lines is NULL in parse_texture_colors\n");
        return (-1);
    }
    i = 0;
    while (lines[i])
    {
        // printf("DEBUG: Processing line %d: [%s]\n", i, lines[i]);
        if (!parse_texture_line(data, lines[i]))
        {
            printf("DEBUG: Error in parse_texture_line, calling free_lines\n");
            free_lines(lines);
            printf("DEBUG: Finished cleanup after parse_texture_line error\n");
            return (-1);
        }
        i++;
    }
    return (1);
}

// int	parse_texture_colors(t_data *data, char **lines, const char *filename)
// {
// 	int	i;
// 	int	map_start;

// 	(void)filename;
// 	i = 0;
// 	while (lines[i])
// 	{
// 		if (!parse_texture_line(data, lines[i]))
// 			return (free_all(data, lines), -1);
// 		i++;
// 	}
// 	if (!data->no_loaded || !data->so_loaded || !data->we_loaded
// 		|| !data->ea_loaded || !data->f_loaded || !data->c_loaded)
// 		return (error_exit("Error: Missing required elements"), -1);
// 	map_start = find_map_start(lines);
// 	if (map_start == -1)
// 		return (error_exit("Error: Invalid map format or missing elements"),
// 			-1);
// 	if (!store_map(data, lines, map_start))
// 		return (error_exit("Error: Failed to store map"), -1);
// 	if (!check_map_valid(data))
// 		return (-1);
// 	return (1);
// }
