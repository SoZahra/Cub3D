/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:13:28 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/15 10:33:01 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	print_parsed_map(char **map)
{
	int	i;

	i = 0;
	printf("\n--- Map ---\n");
	while (map && map[i])
		printf("%s", map[i++]);
	printf("\n----------\n");
}

// void    init_data(t_data *data)
// {
//     data->map = NULL;
//     data->copie_map = NULL;
//     data->no_texture = NULL;
//     data->so_texture = NULL;
//     data->we_texture = NULL;
//     data->ea_texture = NULL;
// 	data->no_loaded = 0;
//     data->so_loaded = 0;
//     data->we_loaded = 0;
//     data->ea_loaded = 0;
// 	data->c_loaded = 0;
//     data->f_loaded = 0;
//     data->n_t = NULL;
//     data->s_t = NULL;
//     data->w_t = NULL;
//     data->e_t = NULL;
//     data->f_color = -1;
//     data->c_color = -1;
//     data->map_width = 0;
//     data->map_height = 0;
// }

void    clean_lines_until(char **lines, int index)
{
    int    i;

    printf("DEBUG: Starting clean_lines_until index %d\n", index);
    i = 0;
    while (i < index)
    {
        if (lines[i])
        {
            free(lines[i]);
        }
        i++;
    }
    free(lines);
}

char	**read_file(const char *filename)
{
	FILE	*file;
	char	**lines;
	char	buffer[1024];
	int		i;

	file = fopen(filename, "r");
	if (!file)
		return (NULL);
	lines = malloc(sizeof(char *) * MAX_LINES);
	if (!lines)
	{
		fclose(file);
		return (NULL);
	}
	i = 0;
	while (fgets(buffer, sizeof(buffer), file) && i < MAX_LINES)
	{
		lines[i] = ft_strdup(buffer);
		// clean_lines_until(lines, i);
		i++;
	}
	lines[i] = NULL;
	fclose(file);
	return (lines);
}

int    main(int ac, char **av)
{
    t_data    data;
    char    **lines;

    if (ac != 2)
        return (printf("Usage: %s <cub_file>\n", av[0]), 1);
    if (!check_arguments(ac, av))
        return (1);
    init_data(&data);
    lines = read_file(av[1]);
    if (!lines)
        return (printf("Failed to read the file\n"), 1);
    if (parse_texture_colors(&data, lines, av[1]) == -1)
        return (free_all(&data, lines), 1);
    free_lines(lines);
    if (!init_game(&data))
    {
		cleanup_mlx(&data);
        free_all(&data, NULL);
        return (1);
    }
	if (data.mlx.mlx && data.mlx.win)
	{
		mlx_loop_hook(data.mlx.mlx, game_loop, &data);
		mlx_loop(data.mlx.mlx);
	}
	cleanup_mlx(&data);
    free_textures(&data);
	free_all(&data, NULL);
    return (0);
}

// int	main(int ac, char **av)
// {
// 	t_data	data;
// 	char	**lines;

// 	if (ac != 2)
// 		return (printf("Usage: %s <cub_file>\n", av[0]), 1);
// 	if (!check_arguments(ac, av))
// 		return (1);
// 	// data = (t_data){0};
// 	init_data(&data);
// 	lines = read_file(av[1]);
// 	if (!lines)
// 		return (printf("Failed to read the file\n"), 1);
// 	if (parse_texture_colors(&data, lines, av[1]) == -1)
// 		return (free_all(&data, lines), 1);
// 	free_lines(lines);
// 	printf("Parsing completed successfully!\n");
// 	if (!init_mlx(&data) || !load_textures(&data))
//     {
//         cleanup_mlx(&data);
//         free_textures(&data);
//         return (1);
//     }
//     draw_background(&data);
//     mlx_loop_hook(data.mlx.mlx, render, &data);
//     mlx_hook(data.mlx.win, 17, 0, (void *)mlx_loop_end, data.mlx.mlx);  // Pour gérer la fermeture de fenêtre
//     mlx_loop(data.mlx.mlx);
//     cleanup_mlx(&data);
//     free_textures(&data);
// 	free_all(&data, lines);
// 	return (0);
// }

	// printf("\n--- Original Map ---\n");
	// for (int i = 0; i < data.map_height; i++)
	// 	printf("[%s]\n", data.map[i]);
	// free_textures(&data),
	// free_map(&data);
	// free_lines(lines);