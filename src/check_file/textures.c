/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:13:26 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/09 18:15:19 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int handle_no_texture(t_data *data, char *cleaned)
{
	if (data->no_loaded)
		return (free(cleaned), error_exit("Error: Duplicate NO texture"), 0);
	if (!check_texture_format(cleaned + 3))
		return (free(cleaned), error_exit("Error: Invalid NO texture format"), 0);
	data->no_texture = ft_strdup(cleaned + 3);
	data->no_loaded = 1;
	return (1);
}

static int handle_so_texture(t_data *data, char *cleaned)
{
	if (data->so_loaded)
		return (free(cleaned), error_exit("Error: Duplicate SO texture"), 0);
	if (!check_texture_format(cleaned + 3))
		return (free(cleaned), error_exit("Error: Invalid SO texture format"), 0);
	data->so_texture = ft_strdup(cleaned + 3);
	data->so_loaded = 1;
	return (1);
}

static int handle_ea_we_texture(t_data *data, char *cleaned, int is_east)
{
	if (is_east)
	{
		if (data->ea_loaded)
			return (free(cleaned), error_exit("Error: Duplicate EA texture"), 0);
		if (!check_texture_format(cleaned + 3))
			return (free(cleaned), error_exit("Error: Invalid EA format"), 0);
		data->ea_texture = ft_strdup(cleaned + 3);
		data->ea_loaded = 1;
	}
	else
	{
		if (data->we_loaded)
			return (free(cleaned), error_exit("Error: Duplicate WE texture"), 0);
		if (!check_texture_format(cleaned + 3))
			return (free(cleaned), error_exit("Error: Invalid WE format"), 0);
		data->we_texture = ft_strdup(cleaned + 3);
		data->we_loaded = 1;
	}
	return (1);
}

static int handle_floor_ceiling(t_data *data, char *cleaned, int is_floor)
{
	if (is_floor)
	{
		if (data->f_loaded)
			return (free(cleaned), error_exit("Error: Duplicate F color"), 0);
		data->f_color = parse_color(cleaned + 2);
		if (data->f_color == -1)
			return (free(cleaned), error_exit("Error: Invalid F color"), 0);
		data->f_loaded = 1;
	}
	else
	{
		if (data->c_loaded)
			return (free(cleaned), error_exit("Error: Duplicate C color"), 0);
		data->c_color = parse_color(cleaned + 2);
		if (data->c_color == -1)
			return (free(cleaned), error_exit("Error: Invalid C color"), 0);
		data->c_loaded = 1;
	}
	return (1);
}

int parse_texture_line(t_data *data, char *line)
{
	char	*cleaned;

	cleaned = clean_line(line);
	if (!cleaned || cleaned[0] == '\0')
		return (free(cleaned), 1);
	if (data->no_loaded && data->so_loaded && data->we_loaded &&
		data->ea_loaded && data->f_loaded && data->c_loaded)
		return (free(cleaned), 1);
	if (!is_valid_identifier(cleaned))
		return (free(cleaned), error_exit("Error: Invalid line"), 0);
	if (ft_strncmp(cleaned, "NO ", 3) == 0 && !handle_no_texture(data, cleaned))
		return (0);
	else if (ft_strncmp(cleaned, "SO ", 3) == 0 && !handle_so_texture(data, cleaned))
		return (0);
	else if (ft_strncmp(cleaned, "EA ", 3) == 0 && !handle_ea_we_texture(data, cleaned, 1))
		return (0);
	else if (ft_strncmp(cleaned, "WE ", 3) == 0 && !handle_ea_we_texture(data, cleaned, 0))
		return (0);
	else if (ft_strncmp(cleaned, "F ", 2) == 0 && !handle_floor_ceiling(data, cleaned, 1))
		return (0);
	else if (ft_strncmp(cleaned, "C ", 2) == 0 && !handle_floor_ceiling(data, cleaned, 0))
		return (0);
	free(cleaned);
	return (1);
}