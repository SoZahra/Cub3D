/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:13:26 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/15 13:45:13 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	no_texture(t_data *data, char *cleaned)
{
	if (!data || !cleaned)
        return (0);
	if (data->no_loaded)
		return (free(cleaned), error_exit("Error: Duplicate NO texture"), 0);
	if (!check_texture_format(cleaned + 3))
		return (free(cleaned), error_exit("Error: Invalid NO texture format"),
			0);
	data->no_texture = ft_strdup(cleaned + 3);
	if (!data->no_texture)
    	return (free(cleaned), 0);
	free(cleaned);
	data->no_loaded = 1;
	return (1);
}

static int	do_texture(t_data *data, char *cleaned)
{
	if (!data || !cleaned)
        return (0);
	if (data->do_loaded)
		return (free(cleaned), error_exit("Error: Duplicate DO texture"), 0);
	if (!check_texture_format(cleaned + 3))
		return (free(cleaned), error_exit("Error: Invalid DO texture format"),
			0);
	data->do_texture = ft_strdup(cleaned + 3);
	if (!data->do_texture)
    	return (free(cleaned), 0);
	free(cleaned);
	data->do_loaded = 1;
	return (1);
}

static int	so_texture(t_data *data, char *cleaned)
{
	if (!data || !cleaned)
        return (0);
	if (data->so_loaded)
		return (free(cleaned), error_exit("Error: Duplicate SO texture"), 0);
	if (!check_texture_format(cleaned + 3))
		return (free(cleaned), error_exit("Error: Invalid SO texture format"),
			0);
	data->so_texture = ft_strdup(cleaned + 3);
	if (!data->so_texture)
    	return (free(cleaned), 0);
	free(cleaned);
	data->so_loaded = 1;
	return (1);
}

static int	ea_we_tex(t_data *data, char *cleaned, int is_east)
{
	if (!data || !cleaned)
        return (0);
	if (is_east)
	{
		if (data->ea_loaded)
			return (free(cleaned), error_exit("Error: Duplicate EA texture"),
				0);
		if (!check_texture_format(cleaned + 3))
			return (free(cleaned), error_exit("Error: Invalid EA format"), 0);
		data->ea_texture = ft_strdup(cleaned + 3);
		if (!data->ea_texture)
    		return (free(cleaned), 0);
		free(cleaned);
		data->ea_loaded = 1;
	}
	else
	{
		if (data->we_loaded)
			return (free(cleaned), error_exit("Error: Duplicate WE texture"),
				0);
		if (!check_texture_format(cleaned + 3))
			return (free(cleaned), error_exit("Error: Invalid WE format"), 0);
		data->we_texture = ft_strdup(cleaned + 3);
		if (!data->we_texture)
			return (free(cleaned), 0);
		free(cleaned);
		data->we_loaded = 1;
	}
	return (1);
}

static int    floor_ceil(t_data *data, char *cleaned, int is_floor)
{
    int ret;

	if (!data || !cleaned)
        return (0);
    if (is_floor)
    {
        if (data->f_loaded)
            return (free(cleaned), error_exit("Error: Duplicate F color"), 0);
        ret = parse_color(cleaned + 2);
        if (ret == -1)
            return (free(cleaned), error_exit("Error: Invalid F color"), 0);
        data->f_color = ret;
        data->f_loaded = 1;
    }
    else
    {
        if (data->c_loaded)
            return (free(cleaned), error_exit("Error: Duplicate C color"), 0);
		if(cleaned[2] == '.' || (cleaned[2] == ' ' && cleaned[3] == '.'))
		{
			if(!check_texture_format(cleaned + 2))
				return (free(cleaned), error_exit("Error: Invalid C format"), 0);
			data->c_texture = ft_strdup(cleaned + 2);
			if (!data->c_texture)
				return (free(cleaned), 0);
			data->c_is_texture = 1;
		}
		else
		{
			ret = parse_color(cleaned + 2);
			if (ret == -1)
				return (free(cleaned), error_exit("Error: Invalid C color"), 0);
			data->c_color = ret;
			data->c_is_texture = 0;
		}
		data->c_loaded = 1;
    }
    free(cleaned);
    return (1);
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

int parse_texture_line(t_data *data, char *line)
{
    char    *cleaned;
    int        ret;

    cleaned = clean_line(line);
    // printf("Processing line: '%s'\n", cleaned); // Debug
    if (!cleaned)
        return (0);
    if (cleaned[0] == '\0')
        return (free(cleaned), 1);
    // printf("Already loaded - NO: %d, SO: %d, WE: %d, EA: %d, DO: %d\n",
        //    data->no_loaded, data->so_loaded, data->we_loaded,
        //    data->ea_loaded, data->do_loaded); // Debug
    if (data->no_loaded && data->so_loaded && data->we_loaded
        && data->ea_loaded && data->f_loaded && data->c_loaded && data->do_loaded)
        return (free(cleaned), 1);
    if (!is_valid_identifier(cleaned))
        return (free(cleaned), error_exit("Error: Invalid line"), 0);
    ret = handle_texture_line_(data, cleaned);
    return (ret);
}
