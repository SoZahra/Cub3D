/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:13:28 by fzayani           #+#    #+#             */
/*   Updated: 2024/11/06 18:29:05 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char **read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return NULL;  // Erreur d'ouverture de fichier
    }

    // Allouer un tableau de MAX_LINES pointeurs vers des chaînes de caractères
    char **lines = malloc(sizeof(char *) * MAX_LINES);
    if (!lines) {
        fclose(file);
        return NULL;  // Échec de l'allocation
    }

    char buffer[1024];  // Tampon pour lire les lignes
    int i = 0;

    while (fgets(buffer, sizeof(buffer), file) && i < MAX_LINES) {
        lines[i] = strdup(buffer);  // Dupliquer chaque ligne lue
        i++;
    }

    fclose(file);
    return lines;
}


int main(int ac, char **av) {
    t_data data;
    char **lines;

    if (ac != 2) {
        printf("Usage: %s <cub_file>\n", av[0]);
        return 1;
    }

    if (!check_arguments(ac, av)) {
        return 1;
    }

    init_data(&data); // Initialiser la structure de données

    // Lire le fichier et obtenir les lignes dans `lines`
    lines = read_file(av[1]);
    if (!lines) {
        printf("Failed to read the file\n");
        return 1;
    }

    // Appeler parse_texture_colors avec les lignes lues et le nom du fichier
    if (parse_texture_colors(&data, lines, av[1]) == -1) {
        printf("Parsing failed\n");
        return 1;
    }

    printf("Parsing completed successfully!\n");

    // Libérer les lignes après usage (si nécessaire)
    // free_lines(lines);

    return 0;
}


// int	main(int ac, char **av)
// {
// 	t_data data;

// 	if (!check_arguments(ac, av))
// 		return (1);
// 	ft_memset(&data, 0, sizeof(t_data)); // Initialiser toute la structure à zéro
// 	if(!parse_cub(&data, av[1]))
// 	{
// 		printf("Parsing failed\n");
// 		return (1);
// 	}
// 	printf("Parsing completed successfully!\n");
// 	return (0);
// }