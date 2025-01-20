/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:49:50 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/20 16:45:39 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	no_texture(t_data *data, char *cleaned)
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

int	do_texture(t_data *data, char *cleaned)
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

int	so_texture(t_data *data, char *cleaned)
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

int	check_ea_texture(t_data *data, char *cleaned)
{
	if (data->ea_loaded)
		return (free(cleaned), error_exit("Error: Duplicate EA texture"), 0);
	if (!check_texture_format(cleaned + 3))
		return (free(cleaned), error_exit("Error: Invalid EA format"), 0);
	data->ea_texture = ft_strdup(cleaned + 3);
	if (!data->ea_texture)
		return (free(cleaned), 0);
	free(cleaned);
	data->ea_loaded = 1;
	return (1);
}

int	check_we_texture(t_data *data, char *cleaned)
{
	if (data->we_loaded)
		return (free(cleaned), error_exit("Error: Duplicate WE texture"), 0);
	if (!check_texture_format(cleaned + 3))
		return (free(cleaned), error_exit("Error: Invalid WE format"), 0);
	data->we_texture = ft_strdup(cleaned + 3);
	if (!data->we_texture)
		return (free(cleaned), 0);
	free(cleaned);
	data->we_loaded = 1;
	return (1);
}
