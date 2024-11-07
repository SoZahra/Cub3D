/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:11:44 by fzayani           #+#    #+#             */
/*   Updated: 2024/11/07 17:30:22 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// int ft_str_is_whitespace(const char *str)
// {
//     while (*str)
//     {
//         if (!(*str == ' ' || *str == '\t')) // Vérifie si le caractère est différent d'un espace ou d'un tab
//             return 0;
//         str++;
//     }
//     return 1;
// }

int ft_str_is_whitespace(const char *str)
{
    while (*str)
	{
        if (*str != ' ' && *str != '\t')
            return 0;  // Retourne 0 si un caractère autre que espace/tabulation est trouvé
        str++;
    }
    return 1;  // Retourne 1 si la chaîne contient uniquement des espaces/tabulations
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
int contains_spaces_in_map(const char *line)
{
	if (line[0] == '\n')
    {
        line++; // Ignore le saut de ligne à la fin de la ligne
		return 1;
	}
    return 0;  // Aucun caractère invalide trouvé
}

int contains_invalid_characters(const char *line)
{
    while (*line) {
        if (*line == '\n') {
            line++; // Ignore le saut de ligne à la fin de la ligne
            continue;
        }
        if (*line != '1' && *line != '0' && *line != 'N' && *line != 'S' && *line != 'W' && *line != 'E'
			&& *line != ' ' && *line != '\t')
			{
            printf("Invalid character '%c' found in line: '%s'\n", *line, line);  // Débogage
            return 1;  // Retourne 1 si un caractère invalide est trouvé
        }
        line++;
    }
    return 0;  // Aucun caractère invalide trouvé
}

int	parse_color(const char *str)
{
	char	**components;

	int r, g, b;
	components = ft_split(str, ',');
	if (ft_arraylen(components) != 3)
		return (-1); // ou une valeur d'erreur spécifique
	r = ft_atoi(components[0]);
	g = ft_atoi(components[1]);
	b = ft_atoi(components[2]);
	ft_free_split(components);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);// erreur: une des valeurs est hors des limites RGB
	return ((r << 16) | (g << 8) | b);
		// Retourne la couleur en un int (format RGB : 0x00RRGGBB)
}

int find_map_end(char **lines)
{
    int i = 0;

    while (lines[i])
    {
        // Si la ligne est vide ou ne contient que des espaces/tabulations, la carte est terminée
        if (ft_str_is_whitespace(lines[i]))
		{
            printf("Map ends at line %d: '%s'\n", i, lines[i]); // Débogage
            return i; // La carte se termine ici
        }
        i++;
    }
    return i; // Si on n'a pas trouvé de fin explicite, on retourne la dernière ligne
}

int validate_after_map(t_data *data, char **lines, int map_end)
{
	(void)data;
    int i = map_end;

    while (lines[i])
    {
        printf("Checking line %d after map: '%s'\n", i, lines[i]);
        if (contains_spaces_in_map(lines[i]))// Vérification des caractères invalides
		{
            printf("Error: Contains space on line %d: '%s'\n", i, lines[i]);
            return -1;
        }
		if(contains_invalid_characters(lines[i]))
		{
			printf("Error: Invalid characters on line %d: '%s'\n", i, lines[i]);
            return -1;
		}
        i++;
    }
    return 0;  // Si aucune erreur n'est trouvée
}


void	init_texture_colors_flags(t_data *data)
{
	data->no_loaded = 0;
    data->so_loaded = 0;
    data->we_loaded = 0;
    data->ea_loaded = 0;
    data->f_loaded = 0;
    data->c_loaded = 0;
}

// int	verify_texture_and_colors(t_data *data)
// {
// 	init_texture_colors_flags(data);
// 	if (data->n_t)
// 		data->no_loaded = 1;
// 	if (data->s_t)
// 		data->so_loaded = 1;
// 	if (data->w_t)
// 		data->we_loaded = 1;
// 	if (data->e_t)
// 		data->ea_loaded = 1;
// 	if (data->f_color != -1)
// 		data->f_loaded = 1;
// 	if (data->c_color != -1)
// 		data->c_loaded = 1;
// 	if (!data->no_loaded || !data->so_loaded || !data->we_loaded
// 		|| !data->ea_loaded || !data->f_loaded || !data->c_loaded)
// 		return (error_exit("Error: Missing one or more textures or colors"),
// 			-1);
// 	return (1);
// }

// int parse_texture_line(t_data *data, char *line)
// {
//     while (ft_isspace(*line)) // Ignore les espaces en début de ligne
//         line++;
//     if (*line == '\0') // Si la ligne est vide, ignore-la
//         return (0);
//     char *trimmed_line = ft_strtrim2(line); // Nettoyer la ligne pour supprimer les espaces et retours à la ligne
// 	printf("Trimmed line: '%s'\n", trimmed_line);
//     // printf("Read line: '%s'\n", trimmed_line); // Affiche la ligne après nettoyage

//     if (ft_strncmp(trimmed_line, "NO ", 3) == 0)
//     {
//         if (data->n_t) // Si la texture NO a déjà été chargée, retourne une erreur
//             return (error_exit("Error: Duplicate NO texture."), 0);
//         data->n_t = ft_strdup(trimmed_line + 3);
//         free(trimmed_line); // Libérer la mémoire allouée pour trimmed_line
//         return (1);
//     }
//     else if (ft_strncmp(trimmed_line, "SO ", 3) == 0)
//     {
//         if (data->s_t) // Si la texture SO a déjà été chargée, retourne une erreur
//             return (error_exit("Error: Duplicate SO texture."), 0);
//         data->s_t = ft_strdup(trimmed_line + 3);
//         free(trimmed_line); // Libérer la mémoire allouée pour trimmed_line
//         return (1);
//     }
//     else if (ft_strncmp(trimmed_line, "WE ", 3) == 0)
//     {
//         if (data->w_t) // Si la texture WE a déjà été chargée, retourne une erreur
//             return (error_exit("Error: Duplicate WE texture."), 0);
//         data->w_t = ft_strdup(trimmed_line + 3);
//         free(trimmed_line); // Libérer la mémoire allouée pour trimmed_line
//         return (1);
//     }
//     else if (ft_strncmp(trimmed_line, "EA ", 3) == 0)
//     {
//         if (data->e_t) // Si la texture EA a déjà été chargée, retourne une erreur
//             return (error_exit("Error: Duplicate EA texture."), 0);
//         data->e_t = ft_strdup(trimmed_line + 3);
//         free(trimmed_line); // Libérer la mémoire allouée pour trimmed_line
//         return (1);
//     }
//     else if (ft_strncmp(trimmed_line, "F ", 2) == 0)
//     {
//         printf("Found F color: '%s'\n", trimmed_line); // Affiche la ligne avec F
//         if (strncmp(trimmed_line, "F", 1) == 0) {
//     // Si une couleur F a déjà été assignée
//     if (data->f_color != -1) {  // Tu utilises -1 comme valeur par défaut non assignée
//         // Extraire les valeurs RGB de la couleur précédente
//         int red = (data->f_color >> 16) & 0xFF;
//         int green = (data->f_color >> 8) & 0xFF;
//         int blue = data->f_color & 0xFF;

//         // Afficher un message d'erreur avec la couleur actuelle et précédente
//         printf("Duplicate F color detected, current: '%s', previous: '%d,%d,%d'\n", trimmed_line, red, green, blue);

//         // Erreur de duplication
//         return 0;
//     }
//     // Sinon, tu assignes la couleur à f_color
//     // Ici, tu pars du principe que tu as déjà extrait les valeurs RGB dans la ligne
//     int r, g, b;
//     // Assure-toi d'extraire correctement les valeurs de la ligne
//     sscanf(trimmed_line, "F %d,%d,%d", &r, &g, &b);

//     // Stocker la couleur dans f_color comme un entier de 24 bits (RGB)
//     data->f_color = (r << 16) | (g << 8) | b;  // Combine RGB dans un seul entier
// }

//         data->f_color = parse_color(trimmed_line + 2); // Utilise la ligne nettoyée
//         free(trimmed_line); // Libérer la mémoire allouée pour trimmed_line
//         return (1);
//     }
//     else if (strncmp(trimmed_line, "C", 1) == 0)
// 	{
// 		// Si une couleur C a déjà été assignée
// 		if (data->c_color != -1) {  // Vérifie si une couleur C a déjà été assignée
// 			// Extraire les valeurs RGB de la couleur précédente
// 			int red = (data->c_color >> 16) & 0xFF;
// 			int green = (data->c_color >> 8) & 0xFF;
// 			int blue = data->c_color & 0xFF;

// 			// Afficher un message d'erreur avec la couleur actuelle et précédente
// 			printf("Duplicate C color detected, current: '%s', previous: '%d,%d,%d'\n", trimmed_line, red, green, blue);

// 			// Erreur de duplication
// 			return 0;
// 		}

// 		// Sinon, on assigne la couleur C
// 		int r, g, b;
// 		sscanf(trimmed_line, "C %d,%d,%d", &r, &g, &b);
// 		data->c_color = (r << 16) | (g << 8) | b;  // Enregistrer la couleur C
// 	}
//     free(trimmed_line); // Libérer la mémoire allouée pour trimmed_line si la ligne n'est pas utilisée
//     return (0);
// }

// int	parse_texture_line(t_data *data, char *line)
// {
// 	while (ft_isspace(*line))
// 		line++;
// 	if (*line == '\0')
// 		return (0);
// 	if (ft_strncmp(line, "NO ", 3) == 0)
// 	{
// 		data->n_t = ft_strdup(line + 3);
// 		// printf("NO texture path loaded: %s\n", data->n_t);
// 		return (1);
// 	}
// 	else if (ft_strncmp(line, "SO ", 3) == 0)
// 	{
// 		data->s_t = ft_strdup(line + 3);
// 		// printf("SO texture path loaded: %s\n", data->s_t);
// 		return (1);
// 	}
// 	else if (ft_strncmp(line, "WE ", 3) == 0)
// 	{
// 		data->w_t = ft_strdup(line + 3);
// 		// printf("WE texture path loaded: %s\n", data->w_t);
// 		return (1);
// 	}
// 	else if (ft_strncmp(line, "EA ", 3) == 0)
// 	{
// 		data->e_t = ft_strdup(line + 3);
// 		// printf("EA texture path loaded: %s\n", data->e_t);
// 		return (1);
// 	}
// 	else if (ft_strncmp(line, "F ", 2) == 0)
// 	{
// 		data->f_color = parse_color(line + 2);
// 		// printf("F color loaded: %d\n", data->f_color);
// 		return (1);
// 	}
// 	else if (ft_strncmp(line, "C ", 2) == 0)
// 	{
// 		data->c_color = parse_color(line + 2);
// 		// printf("C color loaded: %d\n", data->c_color);
// 		return (1);
// 	}
// 	return (0);
// }

int	compare_loaded(t_data *data, char *line) // Si une texture/couleur est chargée, mettez à jour les flags
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		data->no_loaded = 1;
	if (ft_strncmp(line, "SO ", 3) == 0)
		data->so_loaded = 1;
	if (ft_strncmp(line, "WE ", 3) == 0)
		data->we_loaded = 1;
	if (ft_strncmp(line, "EA ", 3) == 0)
		data->ea_loaded = 1;
	if (ft_strncmp(line, "F ", 2) == 0)
		data->f_loaded = 1;
	if (ft_strncmp(line, "C ", 2) == 0)
		data->c_loaded = 1;
	return (0);
}

void print_data_info(t_data *data) {
    printf("NO texture: %s\n", data->no_texture);
    printf("SO texture: %s\n", data->so_texture);
    printf("WE texture: %s\n", data->we_texture);
    printf("EA texture: %s\n", data->ea_texture);
    printf("F color: %d\n", data->f_color);
    printf("C color: %d\n", data->c_color);
    // Ajoute d'autres membres de data si nécessaire
}

int parse_texture_colors(t_data *data, char **lines, const char *filename) {
    int i = 0;
    int map_start = -1;
    // int map_end = -1;

    // Initialiser les drapeaux pour vérifier la présence des textures et couleurs
    init_texture_colors_flags(data);
    // Vérifier si les textures et couleurs sont déjà chargées
    if (!(data->no_loaded && data->so_loaded && data->we_loaded &&
          data->ea_loaded && data->f_loaded && data->c_loaded))
    {
        if (!parse_cub(data, filename))
        {
            printf("Parsing failed\n");
            return -1;
        }
    }
    while (lines[i])
	{  // Lire chaque ligne jusqu'à ce que les six éléments soient chargés
        // Ignorer les lignes vides
        if (lines[i][0] == '\0')
		{
            i++;
            continue;
        }
        if (lines[i][0] == '\t' || lines[i][0] == ' ')// Vérifier si la ligne correspond à une texture ou une couleur
		{
            // Si les six éléments sont chargés, on peut assumer que le reste est la carte
            if (data->no_loaded && data->so_loaded && data->we_loaded &&
                data->ea_loaded && data->f_loaded && data->c_loaded)
            {
                printf("All texture and color elements loaded before map.\n");
                map_start = i; // La carte commence ici
                printf("Map starts at line %d: '%s'\n", i, lines[i]);
                // map_end = find_map_end(&lines[i]);// Trouver la fin de la carte
                // printf("dafafdfdMap ends at line %d\n", map_end);
                break;
            }
            else
			{
                printf("One or more elements not loaded at line %d.\n", i);
                return error_exit("Error: Invalid data before map"), -1;
            }
        }
        i++;
    }
    // Vérification finale des textures et couleurs
    if (map_start == -1)
        return error_exit("Error: No map found"), -1;
    // Validation après la carte (pour vérifier qu'il n'y a pas de caractères indésirables)
    if (validate_after_map(data, lines, map_start) == -1)
        return -1;
    printf("Map starts at line: %d\n", map_start); // Débogage pour visualiser le début de la carte
    return map_start; // Retourne l'index de la première ligne de la carte
}

// int parse_texture_colors(t_data *data, char **lines, const char *filename)
// {
//     int i = 0;
//     int map_start = -1;

//     // Initialiser les drapeaux pour vérifier la présence des textures et couleurs
//     init_texture_colors_flags(data);
//     // Vérifier si les textures et couleurs sont déjà chargées
//     if (!(data->no_loaded && data->so_loaded && data->we_loaded &&
//           data->ea_loaded && data->f_loaded && data->c_loaded))
//     {
//         // Appeler parse_cub avec le chemin du fichier pour charger les textures et couleurs
//         if (!parse_cub(data, filename))
//         {
//             printf("Parsing failed\n");
//             return -1;
//         }
//     }
//     while (lines[i])// Lire chaque ligne jusqu'à ce que les six éléments soient chargés
//     {
//         // Ignorer les lignes vides
//         if (lines[i][0] == '\0' || ft_str_is_whitespace(lines[i]))
//         {
//             i++;
//             continue;
//         }
//         // Vérifier si la ligne correspond à une texture ou une couleur
//         // if (parse_texture_line(data, lines[i]))
//         //     compare_loaded(data, lines[i]);
//         else
//         {
//             // Vérifie si la ligne contient des espaces ou des tabulations
//             if (lines[i][0] == '\t' || lines[i][0] == ' ')
//             {
//                 // Si les six éléments sont chargés, on peut assumer que le reste est la carte
//                 if (data->no_loaded && data->so_loaded && data->we_loaded &&
//                     data->ea_loaded && data->f_loaded && data->c_loaded)
//                 {
//                     printf("All texture and color elements loaded before map.\n");
//                     map_start = i; // La carte commence ici
//                     printf("Map starts at line %d: '%s'\n", i, lines[i]);
//                     break;
//                 }
//                 else
//                 {
//                     printf("One or more elements not loaded at line %d.\n", i);
//                     printf("no_loaded: %d, so_loaded: %d, we_loaded: %d, ea_loaded: %d, f_loaded: %d, c_loaded: %d\n",
//                         data->no_loaded, data->so_loaded, data->we_loaded, data->ea_loaded, data->f_loaded, data->c_loaded);
//                     return error_exit("Error: Invalid data before map"), -1;
//                 }
//             }
//         }
//         i++;
//     }

//     // Vérification finale des textures et couleurs
//     // if (verify_texture_and_colors(data) == -1)
//     //     return -1;

//     // Si aucune carte n'a été trouvée après les éléments, erreur
//     if (map_start == -1)
//         return error_exit("Error: No map found"), -1;

//     printf("Map starts at line: %d\n", map_start); // Débogage pour visualiser le début de la carte
//     return map_start; // Retourne l'index de la première ligne de la carte
// }

void init_data(t_data *data)
{
    data->f_color = -1;
    data->c_color = -1;
    data->so_texture = NULL;
    data->we_texture = NULL;
    data->ea_texture = NULL;
    data->no_texture = NULL;
    data->f_loaded = 0;
    data->c_loaded = 0;
    data->so_loaded = 0;
    data->we_loaded = 0;
    data->ea_loaded = 0;
    data->no_loaded = 0;
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


// Fonction pour traiter les lignes et vérifier les doublons
int check_for_duplicates(t_data *data, const char *line)
{
    if (ft_strncmp2(line, "F ", 2) == 0)
	{
        if (data->f_loaded) {
            printf("Error: Duplicate F color\n");
            return 0;
        }
        // Traitez la couleur F ici
        data->f_loaded = 1;
        printf("Found F color: %s\n", line);
    }
    else if (ft_strncmp2(line, "C ", 2) == 0) {
        if (data->c_loaded) {
            printf("Error: Duplicate C color\n");
            return 0;
        }
        // Traitez la couleur C ici
        data->c_loaded = 1;
        printf("Found C color: %s\n", line);
    }
    else if (ft_strncmp2(line, "SO ", 3) == 0) {
        if (data->so_loaded) {
            printf("Error: Duplicate SO texture\n");
            return 0;
        }
        // Traitez le fichier SO ici
        data->so_loaded = 1;
        printf("Found SO texture: %s\n", line);
    }
    else if (ft_strncmp2(line, "WE ", 3) == 0) {
        if (data->we_loaded) {
            printf("Error: Duplicate WE texture\n");
            return 0;
        }
        // Traitez le fichier WE ici
        data->we_loaded = 1;
        printf("Found WE texture: %s\n", line);
    }
    else if (ft_strncmp2(line, "EA ", 3) == 0) {
        if (data->ea_loaded) {
            printf("Error: Duplicate EA texture\n");
            return 0;
        }
        // Traitez le fichier EA ici
        data->ea_loaded = 1;
        printf("Found EA texture: %s\n", line);
    }
    else if (ft_strncmp2(line, "NO ", 3) == 0) {
        if (data->no_loaded) {
            printf("Error: Duplicate NO texture\n");
            return 0;
        }
        // Traitez le fichier NO ici
        data->no_loaded = 1;
        printf("Found NO texture: %s\n", line);
    }
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
	// Compte le nombre de lignes
	while ((line = get_next_line(fd)))
	{
		free(line);
		lines_count++;
	}
	close(fd);
	// Alloue le tableau de lignes
	lines = malloc((lines_count + 1) * sizeof(char *));
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	// Lecture réelle des lignes
	lines_count = 0;
	while ((line = get_next_line(fd)))
	{
		lines[lines_count++] = line;
		printf("Read line %d: '%s'\n", lines_count, line);
			// Affiche chaque ligne avec des guillemets pour voir les espaces
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

int parse_cub(t_data *data, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file\n");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
	{
        // Nettoyer la ligne (enlever les espaces ou tabulations en début/fin)
        char *trimmed_line = line;
        while (*trimmed_line == ' ' || *trimmed_line == '\t') {
            trimmed_line++;
        }
        if (trimmed_line[ft_strlen(trimmed_line) - 1] == '\n') {
            trimmed_line[ft_strlen(trimmed_line) - 1] = '\0';
        }

        if (!check_for_duplicates(data, trimmed_line)) {
            fclose(file);
            return 0; // Doublon trouvé, donc on quitte
        }
    }

    fclose(file);
    return 1;
}

// int	parse_cub(t_data *data, const char *filename)
// {
// 	char	**lines;
// 	int		map_start;

// 	lines = read_file_lines(filename);
// 	if (!lines)
// 		return (error_exit("Error: Unable to read file"), 0);
// 	map_start = parse_texture_colors(data, lines);
// 	if (map_start == -1) // Vérifie les erreurs lors du parsing
// 	{
// 		free_map(data);
// 		return 0;
// 	}
// 	printf("Map starts at line: %d\n", map_start);
// 		// Affiche l'emplacement du début de la carte
// 	// Valider la carte
// 	if (!validate_map(data, lines, map_start))
// 	{
// 		free_map(data);
// 		return 0;
// 	}
// 	return 1; // Tout va bien
// }
