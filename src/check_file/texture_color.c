/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:38:47 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/10 14:00:20 by fzayani          ###   ########.fr       */
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
