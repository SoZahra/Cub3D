/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:52:12 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/14 15:18:33 by fzayani          ###   ########.fr       */
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

char	*ft_strtrim2(const char *str)
{
	size_t	len;
	char	*trimmed;

	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'
			|| str[len - 1] == '\n'))
		len--;
	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);
	ft_memcpy(trimmed, str, len);
	trimmed[len] = '\0';
	return (trimmed);
}

// void	init_data(t_data *data)
// {
// 	data->f_color = -1;
// 	data->c_color = -1;
// }

char	*clean_line(char *line)
{
	char	*clean;
	int		len;

	clean = ft_strdup(line);
	if(!clean)
		return (NULL);
	len = ft_strlen(clean);
	if (len > 0 && clean[len - 1] == '\n')
		clean[len - 1] = '\0';
	while (len > 0 && (clean[len - 1] == ' ' || clean[len - 1] == '\t'))
		clean[--len] = '\0';
	return (clean);
}

int	is_valid_identifier(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0
		|| ft_strncmp(line, "DO ", 2) == 0);
}
