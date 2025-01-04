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

// void convert_spaces_to_walls(t_data *data)
// {
//     char tmp[data->map_height][data->map_width + 1];

//     for (int y = 0; y < data->map_height; y++)
//         for (int x = 0; x < data->map_width; x++)
//             tmp[y][x] = data->map[y][x];
//     for (int y = 0; y < data->map_height; y++)
//         for (int x = 0; x < data->map_width; x++)
//             if (data->map[y][x] == ' ')
//                 data->copie_map[y][x] = '1';
// }

// void restore_spaces(t_data *data)
// {
//     for (int y = 0; y < data->map_height; y++)
//         for (int x = 0; x < data->map_width; x++)
//             if (data->map[y][x] == '0' && data->copie_map[y][x] != 'V')
//                 return;
//     return;
// }

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

int store_map(t_data *data, char **lines, int start_line)
{
    int height, width;
    int i = 0;
    
    // Compter les lignes de la map
    while (lines[start_line + i])
        i++;
    height = i;
    
    // Trouver la largeur maximale réelle (sans \n)
    width = 0;
    i = 0;
    while (i < height)
    {
        char *line = lines[start_line + i];
        int len = ft_strlen(line);
        // Retirer le \n s'il existe
        if (len > 0 && line[len-1] == '\n')
            len--;
        if (len > width)
            width = len;
        i++;
    }
    data->map = malloc(sizeof(char *) * (height + 1));
    data->copie_map = malloc(sizeof(char *) * (height + 1));
    if (!data->map || !data->copie_map)
        return 0;
    // Copier la map en supprimant les \n
    for (i = 0; i < height; i++)
    {
        char *src_line = lines[start_line + i];
        int line_len = ft_strlen(src_line);
        if (line_len > 0 && src_line[line_len-1] == '\n')
            line_len--;
        data->map[i] = malloc(line_len + 1);
        data->copie_map[i] = malloc(line_len + 1);
        if (!data->map[i] || !data->copie_map[i])
            return 0;
        ft_memcpy(data->map[i], src_line, line_len);
        ft_memcpy(data->copie_map[i], src_line, line_len);
        data->map[i][line_len] = '\0';
        data->copie_map[i][line_len] = '\0';
    }
    data->map[height] = NULL;
    data->copie_map[height] = NULL;
    data->map_height = height;
    data->map_width = width;
    return 1;
}


// int store_map(t_data *data, char **lines, int start_line)
// {
//     int height, width;
//     int i;
    
//     // Compte les lignes de la map
//     i = 0;
//     while (lines[start_line + i])
//     {
//         printf("DEBUG: Checking line %d: [%s]\n", i, lines[start_line + i]);
//         i++;
//     }
//     height = i;
//     printf("DEBUG: Total map height: %d\n", height);
//     width = 0;
//     i = 0;
//     while (i < height)
//     {
//         int len = ft_strlen(lines[start_line + i]);
//         printf("DEBUG: Line %d length: %d\n", i, len);
//         if (len > width)
//             width = len;
//         i++;
//     }
//     printf("DEBUG: Map width: %d\n", width);
//     data->map = malloc(sizeof(char *) * (height + 1));
//     data->copie_map = malloc(sizeof(char *) * (height + 1));
//     if (!data->map || !data->copie_map)
//         return (0);

//     for (i = 0; i < height; i++)
//     {
//         data->map[i] = malloc(sizeof(char) * (width + 1));
//         data->copie_map[i] = malloc(sizeof(char) * (width + 1));
//         if (!data->map[i] || !data->copie_map[i])
//             return (0);

//         // Copier la ligne et la padder avec des espaces
//         int j;
//         for (j = 0; j < width; j++)
//         {
//             if (j < (int)ft_strlen(lines[start_line + i]) && lines[start_line + i][j] != '\n')
//             {
//                 data->map[i][j] = lines[start_line + i][j];
//                 data->copie_map[i][j] = lines[start_line + i][j];
//             }
//             else
//             {
//                 data->map[i][j] = ' ';
//                 data->copie_map[i][j] = ' ';
//             }
//         }
//         data->map[i][width] = '\0';
//         data->copie_map[i][width] = '\0';
//     }

//     data->map[height] = NULL;
//     data->copie_map[height] = NULL;
//     data->map_height = height;
//     data->map_width = width;
//     return (1);
// }

int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == 'V');
}

int is_space_at_beginning(t_data *data, int y, int x)
{
    // Vérifier si c'est un espace au début de la ligne
    int i = 0;
    while (i < x && data->map[y][i] == ' ')
        i++;
    return i == x;
}

int check_space_sequence(t_data *data, int y, int x)
{
    // Si c'est un espace dans une séquence de '1', c'est valide
    // Vérifier d'abord qu'il y a un '1' à gauche
    int left = x - 1;
    while (left >= 0 && data->map[y][left] == ' ')
        left--;
    if (left >= 0 && data->map[y][left] == '1')
    {
        // Vérifier qu'il y a un '1' à droite
        int right = x + 1;
        while (right < data->map_width && data->map[y][right] == ' ')
            right++;
        if (right < data->map_width && data->map[y][right] == '1')
        {
            // Si l'espace est entre deux '1' sur la même ligne, il est valide
            return 1;
        }
    }
    return 0;
}

int is_space_closed(t_data *data, int y, int x)
{
    if (data->map[y][x] != ' ')
        return 1;

    // Ignorer les espaces au début des lignes
    if (is_space_at_beginning(data, y, x))
        return 1;
     if (check_space_sequence(data, y, x))
        return 1;

    // Pour les espaces ailleurs, vérifier qu'ils sont encadrés par des murs
    printf("DEBUG: Checking space at y:%d, x:%d\n", y, x);

    // Vérifier au-dessus
    int up = y - 1;
    while (up >= 0 && data->map[up][x] == ' ')
        up--;
    if (up < 0 || data->map[up][x] != '1')
    {
        printf("DEBUG: Space not closed from above\n");
        return 0;
    }

    // Vérifier en-dessous
    int down = y + 1;
    while (down < data->map_height && data->map[down][x] == ' ')
        down++;
    if (down >= data->map_height || data->map[down][x] != '1')
    {
        printf("DEBUG: Space not closed from below\n");
        return 0;
    }

    // Vérifier à gauche
    int left = x - 1;
    while (left >= 0 && data->map[y][left] == ' ')
        left--;
    if (left < 0 || data->map[y][left] != '1')
    {
        printf("DEBUG: Space not closed from left\n");
        return 0;
    }

    // Vérifier à droite
    int right = x + 1;
    while (right < data->map_width && data->map[y][right] == ' ')
        right++;
    if (right >= data->map_width || data->map[y][right] != '1')
    {
        printf("DEBUG: Space not closed from right\n");
        return 0;
    }

    return 1;
}

int is_border_valid(t_data *data, int y, int x)
{
    // Si on est au-delà de la longueur de la ligne
    int line_len = ft_strlen(data->map[y]);
    if (x >= line_len)
    {
        // Si c'est juste après la ligne, c'est valide si la ligne se termine par un 1
        if (x == line_len && line_len > 0 && data->map[y][line_len-1] == '1')
            return 1;
        printf("DEBUG: Invalid border - position beyond line length at y:%d, x:%d (line length: %d)\n", 
               y, x, line_len);
        return 0;
    }

    // Si c'est un mur, c'est valide
    if (data->map[y][x] == '1')
        return 1;
        
    // Si c'est un espace, il doit être enfermé
    if (data->map[y][x] == ' ')
        return is_space_closed(data, y, x);

    printf("DEBUG: Invalid border character at y:%d, x:%d, char:'%c'\n", 
           y, x, data->map[y][x]);
    return 0;
}

int check_map_borders(t_data *data)
{
    for (int y = 0; y < data->map_height; y++) //toutes les lignes finissent bient par un mur
    {
        int len = ft_strlen(data->map[y]);
        if (data->map[y][len-1] != '1')
        {
            printf("DEBUG: Line %d does not end with a wall\n", y);
            return error_exit("Error: Map line does not end with a wall"), 0;
        }
    }
    int first_len = ft_strlen(data->map[0]);
    int last_len = ft_strlen(data->map[data->map_height-1]);
    for (int x = 0; x < first_len; x++)
    {
        if (!is_border_valid(data, 0, x))
            return 0;
    }
    for (int x = 0; x < last_len; x++)
    {
        if (!is_border_valid(data, data->map_height-1, x))
            return 0;
    }
    return 1;
}

int check_zeros(t_data *data)
{
    for (int y = 1; y < data->map_height - 1; y++)
    {
        for (int x = 1; x < data->map_width - 1; x++)
        {
            if (data->map[y][x] == '0')
            {
                // Vérifier les 4 directions
                if (data->map[y-1][x] == ' ' || data->map[y+1][x] == ' ' ||
                    data->map[y][x-1] == ' ' || data->map[y][x+1] == ' ')
                    return (error_exit("Error: Zero not properly surrounded"), 0);
            }
        }
    }
    return 1;
}

int check_player(t_data *data)
{
    int player_count = 0;
    for (int y = 0; y < data->map_height; y++)
    {
        int line_len = ft_strlen(data->map[y]);
        for (int x = 0; x < line_len; x++)  // Utiliser line_len au lieu de data->map_width
        {
            printf("DEBUG: Checking position y:%d, x:%d, char:'%c'\n", 
                   y, x, data->map[y][x]);  // Debug pour voir ce qu'on trouve
            if (ft_strchr("NSEW", data->map[y][x]))
                player_count++;
        }
    }
    if (player_count != 1)
    {
        printf("DEBUG: Found %d players\n", player_count);  // Debug pour voir combien de joueurs sont trouvés
        return (error_exit("Error: Must have exactly one player"), 0);
    }
    return 1;
}

int check_valid_characters(t_data *data)
{
    for (int y = 0; y < data->map_height; y++)
    {
        int line_len = ft_strlen(data->map[y]);
        for (int x = 0; x < line_len; x++)
        {
            char c = data->map[y][x];
            if (c != '0' && c != '1' && c != ' ' && 
                c != 'N' && c != 'S' && c != 'E' && c != 'W')
            {
                printf("DEBUG: Invalid character '%c' at y:%d, x:%d\n", c, y, x);
                return error_exit("Error: Invalid character in map"), 0;
            }
        }
    }
    return 1;
}

int check_map_valid(t_data *data)
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

// void flood_fill(t_data *data, int x, int y, int *valid)
// {
//     if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height || 
//         data->copie_map[y][x] == '1' || data->copie_map[y][x] == 'V')
//         return;

//     data->copie_map[y][x] = 'V';

//     // Uniquement 4 directions
//     flood_fill(data, x + 1, y, valid);  // droite
//     flood_fill(data, x - 1, y, valid);  // gauche
//     flood_fill(data, x, y + 1, valid);  // bas
//     flood_fill(data, x, y - 1, valid);  // haut
// }



// int check_map_valid(t_data *data)
// {
//     int valid = 1;
//     int player_x = -1, player_y = -1;

//     print_map_state(data, "Map before flood fill");
    
//     find_player_position(data, &player_x, &player_y);
//     if (player_x == -1)
//         return (error_exit("Error: No player found"), 0);
    
//     convert_spaces_to_walls(data);
//     flood_fill(data, player_x, player_y, &valid);
//     print_map_state(data, "Map after flood fill");
//     restore_spaces(data);
//     print_map_state(data, "Map after restoring spaces");
    
//     if (!check_all_zeros_are_visited(data))
//         return (error_exit("Error: Inaccessible areas in map"), 0);

//     return valid;
// }