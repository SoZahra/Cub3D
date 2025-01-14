/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:16:55 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/14 15:19:25 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	is_space_at_beginning(t_data *data, int y, int x)
{
	int	i;

	i = 0;
	while (i < x && (data->map[y][i] == ' '))
		i++;
	return (i == x);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == 'V');
}

int	is_map_char(char c)
{
	return (c == '1' || c == '0' || c == ' ' || ft_strchr("NSEWD", c) != NULL);
}

int	handle_empty_line(char *trimmed)
{
	if (trimmed[0] == '\0' || trimmed[0] == '\n')
	{
		free(trimmed);
		return (1);
	}
	return (0);
}

int	handle_texture_line(char *trimmed, int *f_elements)
{
	if (is_texture_identifier(trimmed))
	{
		(*f_elements)++;
		free(trimmed);
		return (1);
	}
	return (0);
}
