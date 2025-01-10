/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:10:16 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/10 20:33:32 by fzayani          ###   ########.fr       */
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

void    free_textures(t_data *data)
{
    if (data->no_texture)
        free(data->no_texture);
    if (data->so_texture)
        free(data->so_texture);
    if (data->we_texture)
        free(data->we_texture);
    if (data->ea_texture)
        free(data->ea_texture);
    if (data->n_t)
        free(data->n_t);
    if (data->s_t)
        free(data->s_t);
    if (data->w_t)
        free(data->w_t);
    if (data->e_t)
        free(data->e_t);
    data->no_texture = NULL;
    data->so_texture = NULL;
    data->we_texture = NULL;
    data->ea_texture = NULL;
    data->n_t = NULL;
    data->s_t = NULL;
    data->w_t = NULL;
    data->e_t = NULL;
}

void    free_all(t_data *data, char **lines)
{
    if (lines)
        free_lines(lines);
    if (data)
    {
        free_textures(data);
        free_map(data);
    }
}
