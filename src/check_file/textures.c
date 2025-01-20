/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:13:26 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/20 18:49:20 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	handle_ceiling_color(t_data *data, char *cleaned)
{
	int	ret;

	ret = parse_color(cleaned + 2);
	if (ret == -1)
		return (free(cleaned), error_exit("Error: Invalid C color"), 0);
	data->c_color = ret;
	data->c_is_texture = 0;
	return (1);
}

static int	check_ceiling_element(t_data *data, char *cleaned)
{
	if (data->c_loaded)
		return (free(cleaned), error_exit("Error: Duplicate C color"), 0);
	if (cleaned[2] == '.' || (cleaned[2] == ' ' && cleaned[3] == '.'))
	{
		if (!handle_ceiling_texture(data, cleaned))
			return (0);
	}
	else if (!handle_ceiling_color(data, cleaned))
		return (0);
	data->c_loaded = 1;
	return (1);
}

static int	floor_ceil(t_data *data, char *cleaned, int is_floor)
{
	int	ret;

	if (!data || !cleaned)
		return (0);
	if (is_floor)
		ret = check_floor_element(data, cleaned);
	else
		ret = check_ceiling_element(data, cleaned);
	return (ret);
}

static int	handle_texture_line_(t_data *data, char *cleaned)
{
	int	ret;

	if (ft_strncmp(cleaned, "NO ", 3) == 0)
		ret = no_texture(data, cleaned);
	else if (ft_strncmp(cleaned, "SO ", 3) == 0)
		ret = so_texture(data, cleaned);
	else if (ft_strncmp(cleaned, "EA ", 3) == 0)
		ret = ea_we_tex(data, cleaned, 1);
	else if (ft_strncmp(cleaned, "WE ", 3) == 0)
		ret = ea_we_tex(data, cleaned, 0);
	else if (ft_strncmp(cleaned, "DO ", 3) == 0)
		ret = do_texture(data, cleaned);
	else if (ft_strncmp(cleaned, "F ", 2) == 0)
		ret = floor_ceil(data, cleaned, 1);
	else if (ft_strncmp(cleaned, "C ", 2) == 0)
		ret = floor_ceil(data, cleaned, 0);
	else
	{
		free(cleaned);
		ret = 1;
	}
	return (ret);
}

int	parse_texture_line(t_data *data, char *line)
{
	char	*cleaned;
	int		ret;

	cleaned = clean_line(line);
	if (!cleaned)
		return (0);
	if (cleaned[0] == '\0')
		return (free(cleaned), 1);
	if (data->no_loaded && data->so_loaded && data->we_loaded && data->ea_loaded
		&& data->f_loaded && data->c_loaded && data->do_loaded)
		return (free(cleaned), 1);
	if (!is_valid_identifier(cleaned))
		return (free(cleaned), error_exit("Error: Invalid line"), 0);
	ret = handle_texture_line_(data, cleaned);
	if (!ret)
		return (free_textures(data), 0);
	return (ret);
}
