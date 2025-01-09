/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_data_6elements.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:29:52 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/09 16:53:10 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	is_valid_texture_path(const char *path)
{
	char	*temp;
	size_t	len;

	temp = ft_strdup(path);
	len = ft_strlen(temp);
	if (len > 0 && temp[len - 1] == '\n')
		temp[len - 1] = '\0';
	if (ft_strchr(temp, ' '))
	{
		free(temp);
		return (0);
	}
	free(temp);
	return (1);
}

int	is_valid_color_format(const char *str)
{
	while (*str == ' ')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ',' && *str != ' ')
		{
			printf("Invalid character found: '%c'\n", *str);
			return (0);
		}
		str++;
	}
	return (1);
}
