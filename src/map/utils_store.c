/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_store.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:05:37 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/10 15:06:06 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	get_map_height(char **lines, int start_line)
{
	int	height;

	height = 0;
	while (lines[start_line + height])
		height++;
	return (height);
}

int	get_adjusted_len(char *line)
{
	int	len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || !ft_isprint(line[len - 1])))
		len--;
	return (len);
}
