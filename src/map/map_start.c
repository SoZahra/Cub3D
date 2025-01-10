/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:27:13 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/10 14:56:12 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	is_texture_identifier(const char *str)
{
	return (ft_strncmp(str, "NO ", 3) == 0 || ft_strncmp(str, "SO ", 3) == 0
		|| ft_strncmp(str, "WE ", 3) == 0 || ft_strncmp(str, "EA ", 3) == 0
		|| ft_strncmp(str, "F ", 2) == 0 || ft_strncmp(str, "C ", 2) == 0);
}

static int	validate_map_line(char *trimmed)
{
	int	j;

	j = 0;
	while (trimmed[j])
	{
		if (trimmed[j] != ' ' && trimmed[j] != '1' && trimmed[j] != '0'
			&& trimmed[j] != 'N' && trimmed[j] != 'S' && trimmed[j] != 'E'
			&& trimmed[j] != 'W' && trimmed[j] != '\n')
			return (-1);
		j++;
	}
	return (1);
}

static int	check_valid_start(char **lines, char *trimmed, int i)
{
	int	j;
	int	valid_line;

	j = 0;
	valid_line = 0;
	if (validate_map_line(trimmed) == -1)
		return (-1);
	while (trimmed[j])
	{
		if (trimmed[j] == '1')
			valid_line = 1;
		j++;
	}
	if (valid_line)
	{
		printf("DEBUG: Map starts at line %d with content: [%s]\n", i,
			lines[i]);
		return (i);
	}
	return (-1);
}

static int	handle_map_line(char **lines, char *trimmed, int i, int f_elements)
{
	int	ret;

	if (f_elements == 6 && (trimmed[0] == '1' || trimmed[0] == ' '))
	{
		ret = check_valid_start(lines, trimmed, i);
		free(trimmed);
		return (ret);
	}
	free(trimmed);
	return (-2);
}

int	process_line(char **lines, int *i, int *f_elements)
{
	char	*trimmed;

	trimmed = ft_strtrim2(lines[*i]);
	if (!trimmed)
		return (-1);
	if (handle_empty_line(trimmed))
		return (-2);
	if (handle_texture_line(trimmed, f_elements))
		return (-2);
	return (handle_map_line(lines, trimmed, *i, *f_elements));
}
