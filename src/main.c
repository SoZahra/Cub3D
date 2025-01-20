/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:13:28 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/20 20:05:20 by fzayani          ###   ########.fr       */
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

void	clean_lines_until(char **lines, int index)
{
	int	i;

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
		return (free_lines(lines), NULL);
	}
	i = 0;
	while (fgets(buffer, sizeof(buffer), file) && i < MAX_LINES)
	{
		lines[i] = ft_strdup(buffer);
		if (!lines)
			return (free_lines(lines), NULL);
		i++;
	}
	lines[i] = NULL;
	fclose(file);
	return (lines);
}

int	main(int ac, char **av)
{
	t_data	data;
	char	**lines;

	if (ac != 2)
		return (printf("Usage: %s <cub_file>\n", av[0]), 1);
	if (!check_arguments(ac, av))
		return (1);
	init_data(&data);
	lines = read_file(av[1]);
	if (!lines)
		return (free_lines(lines), cleanup_mlx(&data),
			printf("Failed to read the file\n"), 1);
	if (parse_texture_colors(&data, lines, av[1]) == -1
		|| !validate_game_data(&data))
		return (free_all(&data, NULL), free_lines(lines), 1);
	free_lines(lines);
	if (!init_game(&data))
		return (free_all(&data, NULL), 1);
	if (data.mlx.mlx && data.mlx.win)
	{
		mlx_loop_hook(data.mlx.mlx, game_loop, &data);
		mlx_loop(data.mlx.mlx);
	}
	return (cleanup_mlx(&data), free_textures(&data), free_all(&data, NULL), 0);
}
