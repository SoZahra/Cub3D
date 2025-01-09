/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:48:36 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/09 14:20:45 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	print_map_state(t_data *data, char *message)
{
	printf("=== %s ===\n", message);
	for (int y = 0; y < data->map_height; y++)
	{
		printf("Line %2d: [", y);
		for (int x = 0; x < data->map_width; x++)
		{
			printf("%c", data->copie_map[y][x]);
		}
		printf("]\n");
	}
	printf("\n===================\n");
}

void	find_player_position(t_data *data, int *player_x, int *player_y)
{
	char	current;

	*player_x = -1;
	*player_y = -1;
	for (int y = 0; y < data->map_height; y++)
	{
		for (int x = 0; x < data->map_width; x++)
		{
			current = data->copie_map[y][x];
			if (ft_strchr("NSEW", current))
			{
				*player_x = x;
				*player_y = y;
				printf("DEBUG: Found player '%c' at position x:%d, y:%d\n",
					current, x, y);
				return ;
			}
		}
	}
}

int	get_map_dimensions(char **lines, int start_line, int *height, int *width)
{
	int	i;
	int	max_width;
	int	current_width;

	i = start_line;
	max_width = 0;
	*height = 0;
	while (lines[i])
	{
		current_width = ft_strlen(lines[i]);
		if (current_width > max_width)
			max_width = current_width;
		(*height)++;
		i++;
	}
	*width = max_width;
	return (1);
}

int	find_map_start(char **lines)
{
	int		i;
	int		found_elements;
	char	*trimmed;
	int		j;
	int		valid_line;

	i = ((found_elements = 0));
	while (lines[i])
	{
		trimmed = ft_strtrim2(lines[i]);
		if (!trimmed)
			return (-1);
		if (trimmed[0] == '\0' || trimmed[0] == '\n')
		{
			free(trimmed);
			i++;
			continue ;
		}
		if (ft_strncmp(trimmed, "NO ", 3) == 0 || ft_strncmp(trimmed, "SO ",
				3) == 0 || ft_strncmp(trimmed, "WE ", 3) == 0
			|| ft_strncmp(trimmed, "EA ", 3) == 0 || ft_strncmp(trimmed, "F ",
				2) == 0 || ft_strncmp(trimmed, "C ", 2) == 0)
		{
			found_elements++;
		}
		else if (found_elements == 6 && (trimmed[0] == '1'
				|| trimmed[0] == ' '))
		{
			j = 0;
			valid_line = 0;
			while (trimmed[j])
			{
				if (trimmed[j] != ' ' && trimmed[j] != '1' && trimmed[j] != '0'
					&& trimmed[j] != 'N' && trimmed[j] != 'S'
					&& trimmed[j] != 'E' && trimmed[j] != 'W'
					&& trimmed[j] != '\n')
				{
					free(trimmed);
					return (-1);
				}
				if (trimmed[j] == '1')
					valid_line = 1;
				j++;
			}
			if (valid_line)
			{
				free(trimmed);
				printf("DEBUG: Map starts at line %d with content: [%s]\n", i,
					lines[i]);
				return (i);
			}
		}
		free(trimmed);
		i++;
	}
	return (-1);
}

// vérifier si une ligne est une ligne de map valide
int	is_valid_map_line(char *line)
{
	int	found_valid_char;

	found_valid_char = 0;
	while (*line)
	{
		if (*line != ' ' && *line != '1' && *line != '0' && *line != 'N'
			&& *line != 'S' && *line != 'E' && *line != 'W' && *line != '\n')
			return (0);
		if (*line == '1' || *line == '0' || *line == 'N' || *line == 'S'
			|| *line == 'E' || *line == 'W')
			found_valid_char = 1;
		line++;
	}
	return (found_valid_char);
}

int store_map(t_data *data, char **lines, int start_line)
{
    int i;
	int line_len;
    char *src_line;
    int height;
    int width;

	height = ((width = i = 0));
	while (lines[start_line + height])
        height++;
	while(i < height)
	{
        int len = ft_strlen(lines[start_line + i]);
        while (len > 0 && (lines[start_line + i][len - 1] == '\n' || !ft_isprint(lines[start_line + i][len - 1])))
            len--;
        if (len > width)
            width = len;
		i++;
    }
    data->map = malloc(sizeof(char *) * (height + 1));
    data->copie_map = malloc(sizeof(char *) * (height + 1));
	if (!data->map || !data->copie_map)
        return (0);
	i = 0;
	while(i < height)
	{
		data->map[i] = malloc(width + 1);
		data->copie_map[i] = malloc(width + 1);
		if (!data->map[i] || !data->copie_map[i])
            return 0;
		ft_memset(data->map[i], ' ', width);
		ft_memset(data->copie_map[i], ' ', width);
		src_line = lines[start_line + i];
        line_len = ft_strlen(src_line);
        while (line_len > 0 && (src_line[line_len - 1] == '\n' || !ft_isprint(src_line[line_len - 1])))
            line_len--;
		if(line_len > 0)
		{
			ft_memcpy(data->map[i], src_line, line_len);
			ft_memcpy(data->copie_map[i], src_line, line_len);
		}
		i++;
    }
    data->map[height] = NULL;
    data->copie_map[height] = NULL;
    data->map_height = height;
    data->map_width = width;
    return (1);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == 'V');
}

int	is_space_at_beginning(t_data *data, int y, int x)
{
	int	i;

	i = 0;
	while (i < x && (data->map[y][i] == ' '))
		i++;
	return (i == x);
}

int	check_space_sequence(t_data *data, int y, int x)
{
	int	left;
	int	right;

	left = x - 1;
	right = x + 1;
	while (left >= 0 && (data->map[y][left] == ' '))
		left--;
	if (left >= 0 && data->map[y][left] == '1')
	{

		while (right < data->map_width && (data->map[y][right] == ' '))
			right++;
		if (right < data->map_width && data->map[y][right] == '1')
			return (1);
	}
	return (0);
}

int is_space_closed(t_data *data, int y, int x)
{
    int last_char_index;
    if (data->map[y][x] != ' ')
		return (1);
	if (is_space_at_beginning(data, y, x))
		return (1);
	if (check_space_sequence(data, y, x))
		return (1);
	printf("DEBUG: Checking space at y:%d, x:%d\n", y, x);
    last_char_index = data->map_width - 1;
    while (last_char_index >= 0 && data->map[y][last_char_index] == ' ')
        last_char_index--;
    if (x > last_char_index)
        return 1;
    int up = y - 1;
    int down = y + 1;
    int left = x - 1;
    int right = x + 1;
    if (up < 0 || down >= data->map_height || left < 0 || right >= data->map_width)
        return 0;
    if ((data->map[up][x] != '1' && data->map[up][x] != ' ') ||
        (data->map[down][x] != '1' && data->map[down][x] != ' ') ||
        (data->map[y][left] != '1' && data->map[y][left] != ' ') ||
        (data->map[y][right] != '1' && data->map[y][right] != ' '))
        return 0;
    return 1;
}

int	is_border_valid(t_data *data, int y, int x)
{
	int	line_len;

	line_len = ft_strlen(data->map[y]);
	if (x >= line_len)
	{
		if (x == line_len && line_len > 0 && data->map[y][line_len - 1] == '1')
			return 1;
		printf("DEBUG: Invalid border - position beyond line length at y:%d,\
			x:%d (line length: %d)\n", y, x, line_len);
		return 0;
	}
	if (data->map[y][x] == '1')
		return 1;
	if (data->map[y][x] == ' ')
		return is_space_closed(data, y, x);
	printf("DEBUG: Invalid border character at y:%d, x:%d, char:'%c'\n", y, x,
		data->map[y][x]);
	return 0;
}

int check_map_borders(t_data *data)
{
    int last_char_index;
	int line_len;
	int y;
	int x;

	y = ((x = 0));
	while(y < data->map_height)
	{
		line_len = ft_strlen(data->map[y]);
        last_char_index = line_len - 1;
        while (last_char_index >= 0 && data->map[y][last_char_index] == ' ')
            last_char_index--;
        if (last_char_index < 0 || data->map[y][last_char_index] != '1')
		{
            printf("DEBUG: Line %d does not end with a wall\n", y);
            return error_exit("Error: Map line does not end with a wall"), 0;
        }
		if(y == 0 || y == data->map_height - 1)
		{
			while(x < line_len)
			{
				if(data->map[0][x] != '1' && data->map[0][x] != ' ')
				{
					printf("DEBUG: First line has invalid character at x:%d\n", x);
					return error_exit("Error: First map line not valid"), 0;
				}
				x++;
			}
		}
		y++;
    }
    return 1;
}

int	check_zeros(t_data *data)
{
	for (int y = 1; y < data->map_height - 1; y++)
	{
		for (int x = 1; x < data->map_width - 1; x++)
		{
			if (data->map[y][x] == '0')
			{
				if (data->map[y - 1][x] == ' ' || data->map[y + 1][x] == ' '
					|| data->map[y][x - 1] == ' ' || data->map[y][x + 1] == ' ')
					return (error_exit("Error: Zero not properly surrounded"),
						0);
			}
		}
	}
	return 1;
}

int	check_player(t_data *data)
{
	int	player_count;
	int	line_len;

	player_count = 0;
	for (int y = 0; y < data->map_height; y++)
	{
		line_len = ft_strlen(data->map[y]);
		for (int x = 0; x < line_len; x++)
		{
			printf("DEBUG: Checking position y:%d, x:%d, char:'%c'\n", y, x,
				data->map[y][x]);
			if (ft_strchr("NSEW", data->map[y][x]))
				player_count++;
		}
	}
	if (player_count != 1)
	{
		printf("DEBUG: Found %d players\n", player_count);
		return (error_exit("Error: Must have exactly one player"), 0);
	}
	return 1;
}

int	check_valid_characters(t_data *data)
{
	int		line_len;
	char	c;

	for (int y = 0; y < data->map_height; y++)
	{
		line_len = ft_strlen(data->map[y]);
		for (int x = 0; x < line_len; x++)
		{
			c = data->map[y][x];
			if (data->map[y][x] == '\t')
				return(error_exit("Error: map should not have tab"), 0);
			if (c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W')
			{
				printf("DEBUG: Invalid character '%c' at y:%d, x:%d\n", c, y,
					x);
				return error_exit("Error: Invalid character in map"), 0;
			}
		}
	}
	return 1;
}

int	check_map_valid(t_data *data)
{
	print_map_state(data, "Map before validation");
	if (!check_valid_characters(data))
		return 0;
	if (!check_map_borders(data))
		return 0;
	for (int y = 0; y < data->map_height; y++)
	{
		for (int x = 0; x < data->map_width; x++)
		{
			if (!is_space_closed(data, y, x))
				return error_exit("Error: Map has unclosed spaces"), 0;
		}
	}
	if (!check_zeros(data))
		return 0;
	if (!check_player(data))
		return 0;
	print_map_state(data, "Map after validation");
	return 1;
}
