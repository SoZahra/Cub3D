/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:46:40 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/20 15:47:00 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_textures_2(t_data *data)
{
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
}

void	free_textures_3(t_data *data)
{
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
	if (data->c_texture)
	{
		free(data->c_texture);
		data->c_texture = NULL;
	}
	if (data->f_texture)
	{
		free(data->f_texture);
		data->f_texture = NULL;
	}
}
