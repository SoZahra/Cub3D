/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:11:44 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/02 15:46:17 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int validate_color_values(char *str)
{
    int count = 0;
    char **values = ft_split(str, ',');
    if (!values)
        return 0;
        
    while (values[count])
    {
        int val = ft_atoi(values[count]);
        if (val < 0 || val > 255)
            return (ft_free_split(values), 0);
        count++;
    }
    ft_free_split(values);
    return (count == 3);
}

int ft_str_is_whitespace(const char *str)
{
    while (*str)
	{
        if (*str != ' ' && *str != '\t')
            return 0;
        str++;
    }
    return 1;
}

char *ft_strtrim2(const char *str)
{
    while (*str == ' ' || *str == '\t' || *str == '\n') // Ignore les espaces, tabulations et retours à la ligne en début
        str++;
    size_t len = ft_strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\n')) // Et en fin de chaîne
        len--;
    char *trimmed = malloc(len + 1);
    if (!trimmed)
        return (NULL);
    ft_memcpy(trimmed, str, len);
    trimmed[len] = '\0';
    return (trimmed);
}

int parse_color(const char *str)
{
    char **components;
    char *trimmed_str = ft_strtrim2(str);
    int r, g, b;
	int i;

	i = 0;
	while (str[i] && (ft_isdigit(str[i]) || str[i] == ',' || str[i] == ' '))
        i++;
    if (str[i] != '\0' && str[i] != '\n')
        return (free(trimmed_str), -1);
    if (!trimmed_str || !validate_color_values(trimmed_str))
        return (free(trimmed_str), -1);
    components = ft_split(trimmed_str, ',');
    free(trimmed_str);
    if (ft_arraylen(components) != 3)
        return (ft_free_split(components), -1);
    r = ft_atoi(components[0]);
    g = ft_atoi(components[1]);
    b = ft_atoi(components[2]);
    ft_free_split(components);
    return ((r << 16) | (g << 8) | b);
}

void	init_texture_colors_ags(t_data *data)
{
	data->no_loaded = 0;
    data->so_loaded = 0;
    data->we_loaded = 0;
    data->ea_loaded = 0;
    data->f_loaded = 0;
    data->c_loaded = 0;
}

void init_data(t_data *data)
{
    data->f_color = -1;
    data->c_color = -1;
}

int ft_strncmp2(const char *s1, const char *s2, unsigned int n)
{
    unsigned int i = 0;

    if (n == 0)
        return (0);
    while (s1[i] == s2[i] && s1[i] && s2[i] && n - 1 > i)
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *clean_line(char *line) 
{
    char *clean = ft_strdup(line);
    int len = ft_strlen(clean);
    
    if (len > 0 && clean[len-1] == '\n')
        clean[len-1] = '\0';
    while (len > 0 && (clean[len-1] == ' ' || clean[len-1] == '\t'))
        clean[--len] = '\0';
    return clean;
}

int check_texture_format(const char *path)
{
    char **parts = ft_split(path, ' ');
    int result = (ft_arraylen(parts) == 1);
    ft_free_split(parts);
    return result;
}

int is_valid_identifier(char *line)
{
    return (ft_strncmp(line, "NO ", 3) == 0 ||
            ft_strncmp(line, "SO ", 3) == 0 ||
            ft_strncmp(line, "EA ", 3) == 0 ||
            ft_strncmp(line, "WE ", 3) == 0 ||
            ft_strncmp(line, "F ", 2) == 0 ||
            ft_strncmp(line, "C ", 2) == 0);
}

int is_valid_map_line(char *line)
{
    int has_map_char = 0;

    printf("DEBUG: Checking map line: [%s]\n", line);
    while (*line == ' ' || *line == '\t')
        line++;
    while (*line)
    {
        if (*line == '1' || *line == '0' || 
            *line == 'N' || *line == 'S' || 
            *line == 'E' || *line == 'W' || 
            *line == ' ')
        {
            if (*line != ' ')
                has_map_char = 1;
        }
        else
        {
            printf("DEBUG: Invalid character found: '%c'\n", *line);
            return 0;
        }
        line++;
    }
    return has_map_char;
}

int parse_texture_line(t_data *data, char *line)
{
    char *cleaned = clean_line(line);
	printf("DEBUG: Parsing line: [%s]\n", line);
    printf("DEBUG: After cleaning: [%s]\n", cleaned);
	
	if (!cleaned || cleaned[0] == '\0')
        return (free(cleaned), 1);

	if (data->no_loaded && data->so_loaded && data->we_loaded && 
        data->ea_loaded && data->f_loaded && data->c_loaded)
    {
        if (!is_valid_map_line(cleaned))
		{
			printf("DEBUG: Invalid map line detected at: [%s]\n", line);	
            return (free(cleaned), error_exit("Error: Invalid map line"), 0);
		}
        return (free(cleaned), 1);
    }
	if (!is_valid_identifier(cleaned))
        return (free(cleaned), error_exit("Error: Invalid line found between elements"), 0);
    if (ft_strncmp(cleaned, "NO ", 3) == 0)
    {
		if (data->no_loaded)
           return (free(cleaned), error_exit("Error: Duplicate NO texture"), 0);
        if (!check_texture_format(cleaned + 3))
            return (free(cleaned), error_exit("Error: Invalid NO texture format"), 0);
        data->no_texture = ft_strdup(cleaned + 3);
        data->no_loaded = 1;
    }
	else if (ft_strncmp(cleaned, "SO ", 3) == 0)
    {
		if (data->so_loaded)
           return (free(cleaned), error_exit("Error: Duplicate SO texture"), 0);
        if (!check_texture_format(cleaned + 3))
            return (free(cleaned), error_exit("Error: Invalid SO texture format"), 0);
        data->so_texture = ft_strdup(cleaned + 3);
        data->so_loaded = 1;
    }
	else if (ft_strncmp(cleaned, "EA ", 3) == 0)
    {
		if (data->ea_loaded)
           return (free(cleaned), error_exit("Error: Duplicate EA texture"), 0);
        if (!check_texture_format(cleaned + 3))
            return (free(cleaned), error_exit("Error: Invalid EA texture format"), 0);
        data->ea_texture = ft_strdup(cleaned + 3);
        data->ea_loaded = 1;
    }
	else if (ft_strncmp(cleaned, "WE ", 3) == 0)
    {
		if (data->we_loaded)
           return (free(cleaned), error_exit("Error: Duplicate WE texture"), 0);
        if (!check_texture_format(cleaned + 3))
            return (free(cleaned), error_exit("Error: Invalid WE texture format"), 0);
        data->we_texture = ft_strdup(cleaned + 3);
        data->we_loaded = 1;
    }
	else if (ft_strncmp(cleaned, "F ", 2) == 0)
	{
		if (data->f_loaded)
           return (free(cleaned), error_exit("Error: Duplicate F texture"), 0);
		if (!check_texture_format(cleaned + 3))
            return (free(cleaned), error_exit("Error: Invalid F texture format"), 0);
		data->f_color = parse_color(cleaned + 2);
		if (data->f_color == -1)
			return (free(cleaned), error_exit("Error: Invalid F color format"), 0);
		data->f_loaded = 1;
	}
	else if (ft_strncmp(cleaned, "C ", 2) == 0)
	{
		if (data->c_loaded)
           return (free(cleaned), error_exit("Error: Duplicate C texture"), 0);
		if (!check_texture_format(cleaned + 3))
            return (free(cleaned), error_exit("Error: Invalid C texture format"), 0);
		data->c_color = parse_color(cleaned + 2);
		if (data->c_color == -1)
			return (free(cleaned), error_exit("Error: Invalid C color format"), 0);
		data->c_loaded = 1;
	}
    free(cleaned);
    return 1;
}

int parse_texture_colors(t_data *data, char **lines, const char *filename)
{
    (void)filename;
    int i = 0;
    int map_start = -1;

    printf("DEBUG: Starting texture parsing\n");
    
    // Premier passage: charger les textures et couleurs
    while (lines[i]) 
    {
        printf("DEBUG: Processing line %d\n", i);
        if (!parse_texture_line(data, lines[i])) 
            return -1;
        i++;
    }

    // Vérifier que tous les éléments sont chargés
    if (!data->no_loaded || !data->so_loaded || !data->we_loaded ||
        !data->ea_loaded || !data->f_loaded || !data->c_loaded)
        return (error_exit("Error: Missing required elements"), -1);

    // Deuxième passage: trouver le début de la map
    i = 0;
    while (lines[i])
    {
        char *cleaned = clean_line(lines[i]);
        if (cleaned && *cleaned && (*cleaned == '1' || *cleaned == ' '))
        {
            map_start = i;
            free(cleaned);
            break;
        }
        free(cleaned);
        i++;
    }

    printf("DEBUG: Map starts at line %d\n", map_start);

    // Stocker la map
    if (!store_map(data, lines, map_start))
        return (error_exit("Error: Failed to store map"), -1);

    // Vérifier la validité de la map
    if (!check_map_valid(data))
        return -1;

    return 1;
}

char	**read_file_lines(const char *filename)
{
	int		fd;
	int		lines_count;
	char	**lines;
	char	*line;

	lines_count = 0;
	lines = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), NULL);
	while ((line = get_next_line(fd)))
	{
		free(line);
		lines_count++;
	}
	close(fd);
	lines = malloc((lines_count + 1) * sizeof(char *));
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	lines_count = 0;
	while ((line = get_next_line(fd)))
	{
		lines[lines_count++] = line;
		printf("Read line %d: '%s'\n", lines_count, line);
	}
	lines[lines_count] = NULL;
	close(fd);
	return (lines);
}

int parse_map(t_data *data, char **lines)
{
    int i;
    int map_line_count = 0;

    i = 0;
    // Comptage des lignes de la carte
    while (lines[i])
    {
        if (ft_strchr("NSWE01", lines[i][0])) // Ligne de la carte valide
            map_line_count++;
        i++;
    }
    // Allouer de la mémoire pour la carte
    data->map = malloc((map_line_count + 1) * sizeof(char *));
    if (!data->map)
        return (error_exit("Error: Memory allocation for map failed"), -1);
    // Copier les lignes de la carte dans le tableau
    i = 0;
    map_line_count = 0;
    while (lines[i])
    {
        if (ft_strchr("NSWE01", lines[i][0])) // Ligne de la carte valide
        {
            data->map[map_line_count] = ft_strdup(lines[i]);
            if (!data->map[map_line_count])
                return (error_exit("Error: Memory allocation for map line failed"), -1);
            map_line_count++;
        }
        i++;
    }
    data->map[map_line_count] = NULL; // Terminer le tableau de la carte
    return 1;
}

int check_for_duplicates(t_data *data, const char *line)
{
   if (ft_strncmp(line, "F ", 2) == 0)
   {
       if (!is_valid_color_format(line + 2))
           return 0;
       if (data->f_loaded)
           return error_exit("Error: Duplicate F color found."), 0;
       data->f_loaded = 1;
       data->f_color = parse_color(line + 2);
       if (data->f_color == -1)
           return error_exit("Error: Invalid F color values."), 0;
   }
   else if (ft_strncmp(line, "C ", 2) == 0)
   {
       if (!is_valid_color_format(line + 2))
           return 0;
       if (data->c_loaded)  
           return error_exit("Error: Duplicate C color found."), 0;
       data->c_loaded = 1;
       data->c_color = parse_color(line + 2);
       if (data->c_color == -1)
           return error_exit("Error: Invalid C color values."), 0;
   }
   else if (ft_strncmp(line, "NO ", 3) == 0)
   {
       if (data->no_loaded || !is_valid_texture_path(line + 3))
           return error_exit("Error: Invalid or duplicate NO texture."), 0;
       data->no_texture = ft_strdup(line + 3);
       data->no_loaded = 1;
   }
   else if (ft_strncmp(line, "SO ", 3) == 0)
   {
       if (data->so_loaded || !is_valid_texture_path(line + 3))
           return error_exit("Error: Invalid or duplicate SO texture."), 0;
       data->so_texture = ft_strdup(line + 3);
       data->so_loaded = 1;
   }
   else if (ft_strncmp(line, "WE ", 3) == 0)
   {
       if (data->we_loaded || !is_valid_texture_path(line + 3))
           return error_exit("Error: Invalid or duplicate WE texture."), 0;
       data->we_texture = ft_strdup(line + 3);
       data->we_loaded = 1;
   }
   else if (ft_strncmp(line, "EA ", 3) == 0)
   {
       if (data->ea_loaded || !is_valid_texture_path(line + 3))
           return error_exit("Error: Invalid or duplicate EA texture."), 0;
       data->ea_texture = ft_strdup(line + 3);
       data->ea_loaded = 1;
   }
   return 1;
}
