/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:13:28 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/01 17:35:39 by fzayani          ###   ########.fr       */
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
        lines[i] = strdup(buffer); 
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
    {
        printf("Usage: %s <cub_file>\n", av[0]);
        return 1;
    }
	if (!check_arguments(ac, av))
        return 1;
	data = (t_data){0};
    init_data(&data);
    lines = read_file(av[1]);
	if (!lines) 
        return ( printf("Failed to read the file\n"), 1);
	if (parse_texture_colors(&data, lines, av[1]) == -1) 
        return (printf("Parsing failed\n"), 1);
	print_parsed_map(data.map);
    printf("Parsing completed successfully!\n");
	printf("\n--- Textures & Colors ---\n");
	printf("NO: [%s]\n", data.no_texture);
	printf("SO: [%s]\n", data.so_texture);
	printf("WE: [%s]\n", data.we_texture);
	printf("EA: [%s]\n", data.ea_texture);
	printf("F: %d\n", data.f_color);
	printf("C: %d\n", data.c_color);
    // free_lines(lines);
    return 0;
}
