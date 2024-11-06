/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:52:12 by fzayani           #+#    #+#             */
/*   Updated: 2024/11/05 19:09:46 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_arraylen(char **array)
{
	int	len;

	len = 0;
	while (array && array[len])
		len++;
	return (len);
}



int is_empty_line(const char *line)
{
    while (*line)
    {
        if (!ft_isspace(*line))  // Si le caractère n'est pas un espace
            return (0);
        line++;
    }
    return (1);  // Ligne vide ou avec uniquement des espaces
}
