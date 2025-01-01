/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_data_6elements.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:29:52 by fzayani           #+#    #+#             */
/*   Updated: 2024/12/31 19:02:42 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int is_valid_texture_path(const char *path)
{
    char *temp = ft_strdup(path);
    size_t len = ft_strlen(temp);

    if (len > 0 && temp[len-1] == '\n')
        temp[len-1] = '\0';
    if (ft_strchr(temp, ' '))
    {
        free(temp);
        return 0;
    }
    free(temp);
    return 1;
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

