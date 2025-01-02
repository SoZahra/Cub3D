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
	char *line;

	i = 0;
    while (lines[i])
    {
        line = lines[i];
        while (*line && (*line == ' ' || *line == '\t'))
            line++;
        if (*line == '1' || *line == '0')
        {
            printf("DEBUG: Found map start at line %d\n", i);
            return i;
        }
        i++;
    }
    return -1;
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
    int i = 0;
    
    // Compte les lignes de la map
    while (lines[start_line + i])  // Enlever la condition sur [0]
    {
        printf("DEBUG: Checking line %d: [%s]\n", i, lines[start_line + i]);
        i++;
    }
    height = i;
    printf("DEBUG: Total map height: %d\n", height);

    // Trouve la largeur maximale
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

    data->map[height] = NULL;
    data->copie_map[height] = NULL;
    data->map_height = height;
    data->map_width = width;
    return 1;
}

int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == 'V');
}

void flood_fill(t_data *data, int x, int y, int *valid)
{
    // Si hors limites ou déjà visité ou mur
    if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height || 
        data->copie_map[y][x] == '1' || data->copie_map[y][x] == 'V')
        return;

    // Si caractère invalide
    if (!is_valid_char(data->copie_map[y][x]))
    {
        printf("DEBUG: Invalid character '%c' at x:%d, y:%d\n", data->copie_map[y][x], x, y);
        *valid = 0;
        return;
    }

    // Si espace, vérifier qu'il est entouré de murs ou d'autres espaces
    if (data->copie_map[y][x] == ' ')
    {
        char up = (y > 0) ? data->copie_map[y-1][x] : ' ';
        char down = (y < data->map_height-1) ? data->copie_map[y+1][x] : ' ';
        char left = (x > 0) ? data->copie_map[y][x-1] : ' ';
        char right = (x < data->map_width-1) ? data->copie_map[y][x+1] : ' ';

        if ((up != '1' && up != ' ' && up != 'V') ||
            (down != '1' && down != ' ' && down != 'V') ||
            (left != '1' && left != ' ' && left != 'V') ||
            (right != '1' && right != ' ' && right != 'V'))
        {
            printf("DEBUG: Space not enclosed by walls at x:%d, y:%d\n", x, y);
            *valid = 0;
            return;
        }
    }

    // Marquer comme visité
    data->copie_map[y][x] = 'V';

    // Récursion dans les 8 directions (incluant diagonales)
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            flood_fill(data, x + dx, y + dy, valid);
        }
    }
}


int check_map_valid(t_data *data)
{
    int valid = 1;
    int player_x = -1, player_y = -1;

    print_map_state(data, "Map before flood fill");

    find_player_position(data, &player_x, &player_y);
    if (player_x == -1)
        return (error_exit("Error: No player found"), 0);

    flood_fill(data, player_x, player_y, &valid);
    print_map_state(data, "Map after flood fill");

    if (!check_all_zeros_are_visited(data))
        return (error_exit("Error: Inaccessible areas in map"), 0);

    return 1;
}

//int check_map_valid(t_data *data)
//{
//    int valid = 1;
//    int start_x = -1, start_y = -1;
    
//    // Debug: Afficher la map avant flood fill
//    printf("\nBefore flood fill:\n");
//    for (int y = 0; y < data->map_height; y++)
//        printf("[%s]\n", data->copie_map[y]);

//    // Trouver le point de départ
//    printf("\nSearching for starting position...\n");
//    for (int y = 0; y < data->map_height; y++)
//    {
//        for (int x = 0; x < data->map_width; x++)
//        {
//            if (ft_strchr("NSEW", data->copie_map[y][x]))
//            {
//                start_x = x;
//                start_y = y;
//                printf("Found starting position at x:%d, y:%d\n", x, y);
//                break;
//            }
//        }
//        if (start_x != -1)
//            break;
//    }
//    if (start_x == -1)
//        return (error_exit("Error: No starting position found"), 0);
//    printf("Starting flood fill at x:%d, y:%d\n", start_x, start_y);
//    flood_fill(data, start_x, start_y, &valid);
	
//    printf("\nAfter flood fill:\n");
//    for (int y = 0; y < data->map_height; y++)
//        printf("[%s]\n", data->copie_map[y]);

//    if (!valid)
//        return (error_exit("Error: Map is not closed"), 0);
//    return 1;
//}
