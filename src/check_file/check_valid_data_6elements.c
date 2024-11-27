/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_data_6elements.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:29:52 by fzayani           #+#    #+#             */
/*   Updated: 2024/11/08 18:00:10 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int is_valid_texture_path(const char *path)
{
	while(*path)
	{
		if(!ft_isalnum(*path) && *path != '/' && *path != '.' && *path != '_')
			return (0);
		path++;
	}
	return (1);
}

int is_valid_color_format(const char *str)
{
    while (*str == ' ') // Ignorer les espaces en début de ligne
        str++;
    while (*str)
    {
        if (!ft_isdigit(*str) && *str != ',' && *str != ' ')
        {
            printf("Invalid character found: '%c'\n", *str); // Ajout de débogage
            return 0;
        }
        str++;
    }
    return 1;
}

