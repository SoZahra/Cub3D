/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:41:59 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/20 20:02:03 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->f_color = -1;
	data->c_color = -1;
	data->movement.move_speed = 0.1;
	data->movement.rot_speed = 0.05;
}

int	validate_game_data(t_data *data)
{
	if (!data->no_texture || !data->so_texture || !data->we_texture
		|| !data->ea_texture || !data->do_texture || !data->f_texture)
		return (0);
	if (!check_texture_format(data->no_texture)
		|| !check_texture_format(data->so_texture)
		|| !check_texture_format(data->we_texture)
		|| !check_texture_format(data->ea_texture)
		|| !check_texture_format(data->do_texture)
		|| !check_texture_format(data->f_texture))
		return (0);
	return (1);
}

int	init_game(t_data *data)
{
	t_ray	initial_ray;

	if (!validate_game_data(data))
		return (0);
	if (!init_mlx(data))
		return (0);
	if (!check_player(data))
		return (cleanup_mlx(data), 0);
	if (!load_textures(data))
		return (cleanup_mlx(data), 0);
	if (!init_doors(data))
		return (cleanup_mlx(data), 0);
	init_minimap(data);
	init_player_pos(&initial_ray, data);
	raycasting(data);
	init_hooks(data);
	return (1);
}
