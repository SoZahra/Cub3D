/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:48:36 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/02 17:47:22 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void print_map_state(t_data *data, char *message)
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

void find_player_position(t_data *data, int *player_x, int *player_y)
{
    *player_x = -1;
    *player_y = -1;

    for (int y = 0; y < data->map_height; y++)
    {
        for (int x = 0; x < data->map_width; x++)
        {
            char current = data->copie_map[y][x];
            if (ft_strchr("NSEW", current))
            {
                *player_x = x;
                *player_y = y;
                printf("DEBUG: Found player '%c' at position x:%d, y:%d\n", 
                       current, x, y);
                return;
            }
        }
    }
}

void convert_spaces_to_walls(t_data *data)
{
    char tmp[data->map_height][data->map_width + 1];

    for (int y = 0; y < data->map_height; y++)
        for (int x = 0; x < data->map_width; x++)
            tmp[y][x] = data->map[y][x];
    for (int y = 0; y < data->map_height; y++)
        for (int x = 0; x < data->map_width; x++)
            if (data->map[y][x] == ' ')
                data->copie_map[y][x] = '1';
}

void restore_spaces(t_data *data)
{
    for (int y = 0; y < data->map_height; y++)
        for (int x = 0; x < data->map_width; x++)
            if (data->map[y][x] == '0' && data->copie_map[y][x] != 'V')
                return;
    return;
}

int get_map_dimensions(char **lines, int start_line, int *height, int *width)
{
    int i;
    int max_width;

	i = start_line;
	max_width = 0;
    *height = 0;
    while (lines[i])
    {
        int current_width = ft_strlen(lines[i]);
        if (current_width > max_width)
            max_width = current_width;
        (*height)++;
        i++;
    }
    *width = max_width;
    return 1;
}

int find_map_start(char **lines)
{
    int i;
    int found_elements;

    i = 0;
    found_elements = 0;

    // Parcourir toutes les lignes
    while (lines[i])
    {
        char *trimmed = ft_strtrim2(lines[i]);
        if (!trimmed)
            return (-1);

        // Ignorer les lignes vides
        if (trimmed[0] == '\0' || trimmed[0] == '\n')
        {
            free(trimmed);
            i++;
            continue;
        }

        // Compter les éléments trouvés (NO, SO, WE, EA, F, C)
        if (ft_strncmp(trimmed, "NO ", 3) == 0 || ft_strncmp(trimmed, "SO ", 3) == 0 ||
            ft_strncmp(trimmed, "WE ", 3) == 0 || ft_strncmp(trimmed, "EA ", 3) == 0 ||
            ft_strncmp(trimmed, "F ", 2) == 0 || ft_strncmp(trimmed, "C ", 2) == 0)
        {
            found_elements++;
        }
        // Si on trouve un '1' ou un '0' après avoir trouvé tous les éléments
        else if (found_elements == 6 && (trimmed[0] == '1' || trimmed[0] == ' '))
        {
            // Vérifier que la ligne contient bien des caractères valides de map
            int j = 0;
            int valid_line = 0;
            while (trimmed[j])
            {
                if (trimmed[j] != ' ' && trimmed[j] != '1' && trimmed[j] != '0' &&
                    trimmed[j] != 'N' && trimmed[j] != 'S' && trimmed[j] != 'E' &&
                    trimmed[j] != 'W' && trimmed[j] != '\n')
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
                printf("DEBUG: Map starts at line %d with content: [%s]\n", i, lines[i]);
                return (i);
            }
        }
        free(trimmed);
        i++;
    }
    return (-1);
}

// Fonction utilitaire pour vérifier si une ligne est une ligne de map valide
int is_valid_map_line(char *line)
{
    int found_valid_char = 0;
    
    while (*line)
    {
        if (*line != ' ' && *line != '1' && *line != '0' &&
            *line != 'N' && *line != 'S' && *line != 'E' &&
            *line != 'W' && *line != '\n')
            return (0);
        if (*line == '1' || *line == '0' ||
            *line == 'N' || *line == 'S' ||
            *line == 'E' || *line == 'W')
            found_valid_char = 1;
        line++;
    }
    return (found_valid_char);
}

int check_all_zeros_are_visited(t_data *data)
{
    for (int y = 0; y < data->map_height; y++)
    {
        for (int x = 0; x < data->map_width; x++)
        {
            if (data->map[y][x] == '0')
            {
                // Si on trouve un '0' non visité (non marqué 'V')
                if (data->copie_map[y][x] != 'V')
                {
                    printf("DEBUG: Found unvisited zero at x:%d, y:%d\n", x, y);
                    return 0;
                }
            }
        }
    }
    return 1;
}


///fonction a refaire 
int store_map(t_data *data, char **lines, int start_line)
{
    int height, width;
    int i;
    
    // Compte les lignes de la map
    i = 0;
    while (lines[start_line + i])
    {
        printf("DEBUG: Checking line %d: [%s]\n", i, lines[start_line + i]);
        i++;
    }
    height = i;
    printf("DEBUG: Total map height: %d\n", height);
    width = 0;
    i = 0;
    while (i < height)
    {
        int len = ft_strlen(lines[start_line + i]);
        printf("DEBUG: Line %d length: %d\n", i, len);
        if (len > width)
            width = len;
        i++;
    }
    printf("DEBUG: Map width: %d\n", width);
    data->map = malloc(sizeof(char *) * (height + 1));
    data->copie_map = malloc(sizeof(char *) * (height + 1));
    if (!data->map || !data->copie_map)
        return (0);

    for (i = 0; i < height; i++)
    {
        data->map[i] = malloc(sizeof(char) * (width + 1));
        data->copie_map[i] = malloc(sizeof(char) * (width + 1));
        if (!data->map[i] || !data->copie_map[i])
            return (0);

        // Copier la ligne et la padder avec des espaces
        int j;
        for (j = 0; j < width; j++)
        {
            if (j < (int)ft_strlen(lines[start_line + i]) && lines[start_line + i][j] != '\n')
            {
                data->map[i][j] = lines[start_line + i][j];
                data->copie_map[i][j] = lines[start_line + i][j];
            }
            else
            {
                data->map[i][j] = ' ';
                data->copie_map[i][j] = ' ';
            }
        }
        data->map[i][width] = '\0';
        data->copie_map[i][width] = '\0';
    }

    data->map[height] = NULL;
    data->copie_map[height] = NULL;
    data->map_height = height;
    data->map_width = width;
    return (1);
}

int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == 'V');
}

void flood_fill(t_data *data, int x, int y, int *valid)
{
    if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height || 
        data->copie_map[y][x] == '1' || data->copie_map[y][x] == 'V')
        return;

    data->copie_map[y][x] = 'V';

    // Uniquement 4 directions
    flood_fill(data, x + 1, y, valid);  // droite
    flood_fill(data, x - 1, y, valid);  // gauche
    flood_fill(data, x, y + 1, valid);  // bas
    flood_fill(data, x, y - 1, valid);  // haut
}

// void flood_fill(t_data *data, int x, int y, int *valid)
// {
//     // Si hors limites ou déjà visité ou mur
//     if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height || 
//         data->copie_map[y][x] == '1' || data->copie_map[y][x] == 'V')
//         return;

//     // Si caractère invalide
//     if (!is_valid_char(data->copie_map[y][x]))
//     {
//         printf("DEBUG: Invalid character '%c' at x:%d, y:%d\n", data->copie_map[y][x], x, y);
//         *valid = 0;
//         return;
//     }

//     // Si espace, vérifier qu'il est entouré de murs ou d'autres espaces
//     if (data->copie_map[y][x] == ' ')
//     {
//         char up = (y > 0) ? data->copie_map[y-1][x] : ' ';
//         char down = (y < data->map_height-1) ? data->copie_map[y+1][x] : ' ';
//         char left = (x > 0) ? data->copie_map[y][x-1] : ' ';
//         char right = (x < data->map_width-1) ? data->copie_map[y][x+1] : ' ';

//         if ((up != '1' && up != ' ' && up != 'V') ||
//             (down != '1' && down != ' ' && down != 'V') ||
//             (left != '1' && left != ' ' && left != 'V') ||
//             (right != '1' && right != ' ' && right != 'V'))
//         {
//             printf("DEBUG: Space not enclosed by walls at x:%d, y:%d\n", x, y);
//             *valid = 0;
//             return;
//         }
//     }

//     // Marquer comme visité
//     data->copie_map[y][x] = 'V';

//     // Récursion dans les 8 directions (incluant diagonales)
//     for (int dy = -1; dy <= 1; dy++)
//     {
//         for (int dx = -1; dx <= 1; dx++)
//         {
//             flood_fill(data, x + dx, y + dy, valid);
//         }
//     }
// }


int check_map_valid(t_data *data)
{
    int valid = 1;
    int player_x = -1, player_y = -1;

    print_map_state(data, "Map before flood fill");
    
    find_player_position(data, &player_x, &player_y);
    if (player_x == -1)
        return (error_exit("Error: No player found"), 0);
    
    convert_spaces_to_walls(data);
    flood_fill(data, player_x, player_y, &valid);
    print_map_state(data, "Map after flood fill");
    restore_spaces(data);
    print_map_state(data, "Map after restoring spaces");
    
    if (!check_all_zeros_are_visited(data))
        return (error_exit("Error: Inaccessible areas in map"), 0);

    return valid;
}
