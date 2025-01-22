/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:38:47 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/22 11:25:13 by lanani-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	validate_color_values(char *str)
{
	int		count;
	char	**values;
	int		val;

	count = 0;
	values = ft_split(str, ',');
	if (!values)
		return (0);
	while (values[count])
	{
		val = ft_atoi(values[count]);
		if (val < 0 || val > 255)
			return (ft_free_split(values), 0);
		count++;
	}
	ft_free_split(values);
	return (count == 3);
}

int	load_wall_textures(t_data *data)
{
	int		i;
	char	*paths[4];

	i = 0;
	paths[0] = "textures/1.xpm";
	paths[1] = "textures/2.xpm";
	paths[2] = "textures/3.xpm";
	paths[3] = "textures/4.xpm";
	data->wall_tex.num_frames = 4;
	data->wall_tex.animation_time = 0.0;
	while (i < data->wall_tex.num_frames)
	{
		if (!load_texture(data, &data->wall_tex.frames[i], paths[i]))
			return (0);
		i++;
	}
	return (1);
}
