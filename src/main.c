/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:13:28 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/02 15:45:21 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


void print_parsed_map(char **map)
{
    int i = 0;
    printf("\n--- Map ---\n");
    while (map && map[i])
        printf("%s", map[i++]);
    printf("\n----------\n");
}

char **read_file(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (!file) 
        return NULL;
    char **lines = malloc(sizeof(char *) * MAX_LINES);
    if (!lines) 
	{
        fclose(file);
        return NULL;
    }
    char buffer[1024];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file) && i < MAX_LINES) 
	{
        lines[i] = ft_strdup(buffer); 
        i++;
    }
    fclose(file);
    return lines;
}

int main(int ac, char **av)
{
    t_data data;
    char **lines;

	if (ac != 2)
        return (printf("Usage: %s <cub_file>\n", av[0]), 1);
	if (!check_arguments(ac, av))
        return 1;
	data = (t_data){0};
    init_data(&data);
    lines = read_file(av[1]);
	if (!lines) 
        return ( printf("Failed to read the file\n"), 1);
	if (parse_texture_colors(&data, lines, av[1]) == -1) 
        return (free_lines(lines), printf("Parsing failed\n"), 1);
	//print_parsed_map(data.map);
    printf("Parsing completed successfully!\n");
	printf("\n--- Original Map ---\n");
    for (int i = 0; i < data.map_height; i++)
        printf("[%s]\n", data.map[i]);

    // printf("\n--- Flood Fill Result ---\n");
	// for (int i = 0; i < data.map_height; i++)
    //     printf("%s", data.copie_map[i]);
    //free_lines(lines);
    free_map(&data);
    return 0;
}
