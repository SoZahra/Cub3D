/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:10:16 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/15 16:35:27 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_map(t_data *data)
{
	int	i;

	if (data->map)
	{
		i = 0;
		while (data->map[i])
			free(data->map[i++]);
		free(data->map);
		data->map = NULL;
	}
	if (data->copie_map)
	{
		i = 0;
		while (data->copie_map[i])
			free(data->copie_map[i++]);
		free(data->copie_map);
		data->copie_map = NULL;
	}
}

void	ft_free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void    free_lines(char **lines)
{
    int    i;

    if (!lines)
        return ;
    i = 0;
    while (lines && lines[i])
    {
        if (lines[i])
            free(lines[i]);
        lines[i] = NULL;
        i++;
    }
    free(lines);
}

void free_textures(t_data *data)
{
    if (!data)
        return;
    if (data->no_texture)
    {
        free(data->no_texture);
        data->no_texture = NULL;
    }
    if (data->so_texture)
    {
        free(data->so_texture);
        data->so_texture = NULL;
    }
    if (data->we_texture)
    {
        free(data->we_texture);
        data->we_texture = NULL;
    }
    if (data->ea_texture)
    {
        free(data->ea_texture);
        data->ea_texture = NULL;
    }
    if (data->do_texture)
    {
        free(data->do_texture);
        data->do_texture = NULL;
    }
    data->n_t = NULL;
    data->s_t = NULL;
    data->w_t = NULL;
    data->e_t = NULL;
    data->do_t = NULL;
}

void free_all(t_data *data, char **lines)
{
    if (!data)
        return;
    if (data->doors)
    {
        free(data->doors);
        data->doors = NULL;
    }
    free_map(data);
    free_textures(data);
    if (lines)
        free_lines(lines);
}
