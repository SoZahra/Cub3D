/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:10:16 by fzayani           #+#    #+#             */
/*   Updated: 2024/11/05 18:50:59 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		while (i < data->map_height)
		{
			if (data->map[i])
				free(data->map[i]);
			i++;
		}
		free(data->map);
	}
	i = 0;
	if (data->copie_map)
	{
		while (i < data->map_height)
		{
			if (data->copie_map[i])
				free(data->copie_map[i]);
			i++;
		}
		free(data->copie_map);
	}
}
void	ft_free_split(char **array)
{
	int i;

	if (!array)
		return;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

