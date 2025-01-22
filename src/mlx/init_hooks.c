/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:20:05 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/22 11:49:35 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// int	handle_keypress(int keycode, t_data *data)
// {
// 	if (keycode == KEY_ESC)
// 		exit_game(data);
// 	else if (keycode == KEY_W)
// 		data->movement.forward = 1;
// 	else if (keycode == KEY_S)
// 		data->movement.backward = 1;
// 	else if (keycode == KEY_A)
// 		data->movement.left = 1;
// 	else if (keycode == KEY_D)
// 		data->movement.right = 1;
// 	return (0);
// }

// int	handle_keyrelease(int keycode, t_data *data)
// {
// 	if (keycode == KEY_W)
// 		data->movement.forward = 0;
// 	else if (keycode == KEY_S)
// 		data->movement.backward = 0;
// 	else if (keycode == KEY_A)
// 		data->movement.left = 0;
// 	else if (keycode == KEY_D)
// 		data->movement.right = 0;
// 	return (0);
// }

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		exit_game(data);
	if (keycode == KEY_W)
		data->movement.forward = 1;
	if (keycode == KEY_S)
		data->movement.backward = 1;
	if (keycode == KEY_A)
		data->movement.left = 1;
	if (keycode == KEY_D)
		data->movement.right = 1;
	if (keycode == KEY_RIGHT)
		data->movement.rot_left = 1;
	if (keycode == KEY_LEFT)
		data->movement.rot_right = 1;
	if (keycode == 'e' || keycode == 'E')
		data->keys.e = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->movement.forward = 0;
	if (keycode == KEY_S)
		data->movement.backward = 0;
	if (keycode == KEY_A)
		data->movement.left = 0;
	if (keycode == KEY_D)
		data->movement.right = 0;
	if (keycode == KEY_RIGHT)
		data->movement.rot_left = 0;
	if (keycode == KEY_LEFT)
		data->movement.rot_right = 0;
	if (keycode == 'e' || keycode == 'E')
		data->keys.e = 0;
	return (0);
}

int	exit_game(t_data *data)
{
	cleanup_mlx(data);
	free_all(data, NULL);
	exit(0);
	return (0);
}

int	handle_mouse(int x, int y, t_data *data)
{
	int		mouse_diff;
	double	rotation_angle;

	(void)y;
	mouse_diff = x - data->movement.prev_mouse_x;
	if (mouse_diff != 0)
	{
		rotation_angle = (mouse_diff * ROT_SPEED);
		rotate_vectors(data, rotation_angle);
	}
	data->movement.prev_mouse_x = x;
	return (0);
}

void	init_hooks(t_data *data)
{
	if (!data || !data->mlx.mlx || !data->mlx.win || !data->img.img
		|| !data->img.addr)
		return ;
	mlx_loop_hook(data->mlx.mlx, game_loop, data);
	mlx_hook(data->mlx.win, 17, 0, exit_game, data);
	mlx_hook(data->mlx.win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx.win, MotionNotify, PointerMotionMask, handle_mouse,
		data);
}
