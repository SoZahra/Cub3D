/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:25:54 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/21 17:07:37 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ea_we_tex(t_data *data, char *cleaned, int is_east)
{
	if (!data || !cleaned)
		return (0);
	if (is_east)
		return (check_ea_texture(data, cleaned));
	return (check_we_texture(data, cleaned));
}

int	handle_floor_texture(t_data *data, char *cleaned)
{
	int		i;
	char	*clean_path;

	i = 1;
	while (cleaned[i] && cleaned[i] == ' ')
		i++;
	if (!check_texture_format(cleaned + 2))
		return (free(cleaned), error_exit("Error: Invalid F format"), 0);
	clean_path = clean_texture_path(cleaned + 2);
	if (!clean_path)
		return (free(cleaned), 0);
	data->f_texture = clean_path;
	data->f_is_texture = 1;
	return (free(cleaned), 1);
}

int	check_floor_color(t_data *data, char *cleaned)
{
	int	ret;

	ret = parse_color(cleaned + 2);
	if (ret == -1)
		return (free(cleaned), error_exit("Error: Invalid F color"), 0);
	data->f_color = ret;
	data->f_is_texture = 0;
	free(cleaned);
	return (1);
}

int	check_floor_element(t_data *data, char *cleaned)
{
	int	i;

	if (data->f_loaded)
		return (free(cleaned), error_exit("Error: Duplicate F color"), 0);
	i = 1;
	while (cleaned[i] && cleaned[i] == ' ')
		i++;
	if (cleaned[i] == '.' || (cleaned[i] == ' ' && cleaned[i + 1] == '.'))
	{
		if (!handle_floor_texture(data, cleaned))
			return (0);
	}
	else
	{
		if (!check_floor_color(data, cleaned))
			return (0);
	}
	data->f_loaded = 1;
	return (1);
}

int	handle_ceiling_texture(t_data *data, char *cleaned)
{
	int		i;
	char	*clean_path;

	i = 1;
	while (cleaned[i] && cleaned[i] == ' ')
		i++;
	if (!check_texture_format(cleaned + 2))
		return (free(cleaned), error_exit("Error: Invalid C format"), 0);
	clean_path = clean_texture_path(cleaned + 2);
	if (!clean_path)
		return (free(cleaned), 0);
	data->c_texture = clean_path;
	data->c_is_texture = 1;
	return (free(cleaned), 1);
}
