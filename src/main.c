/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:13:28 by fzayani           #+#    #+#             */
/*   Updated: 2024/11/01 19:11:04 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int ac, char **av)
{
	// t_data	data;

	if (!check_arguments(ac, av))
		return (1);
	// ft_memset(&data, 0, sizeof(data));
	// load_map(av[1], &data);
	// check_map(&data);
	// find_p_position(&data);
	// load_map_copie(&data);
	// if (!check_valid_path(&data))
	// {
	// 	ft_printf("Invalid map: not all collectibles\
    //             or the exit are reachable.\n");
	// 	free_map(&data);
	// 	return (1);
	// }
	// init_mlx(&data);
	// load_images(&data);
	// draw_map(&data);
	// setup_hooks(&data);
	// end_game(&data);
	return (0);
}