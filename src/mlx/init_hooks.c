/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:20:05 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/14 11:06:03 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// Gestionnaire de touche pressée
int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		exit_game(data);
	else if (keycode == KEY_W)
		data->movement.forward = 1;
	else if (keycode == KEY_S)
		data->movement.backward = 1;
	else if (keycode == KEY_A)
		data->movement.left = 1;
	else if (keycode == KEY_D)
		data->movement.right = 1;
	else if (keycode == KEY_LEFT)
		data->movement.rot_left = 1;
	else if (keycode == KEY_RIGHT)
		data->movement.rot_right = 1;
	return (0);
}

// Gestionnaire de touche relâchée
int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->movement.forward = 0;
	else if (keycode == KEY_S)
		data->movement.backward = 0;
	else if (keycode == KEY_A)
		data->movement.left = 0;
	else if (keycode == KEY_D)
		data->movement.right = 0;
	else if (keycode == KEY_LEFT)
		data->movement.rot_left = 0;
	else if (keycode == KEY_RIGHT)
		data->movement.rot_right = 0;
	return (0);
}

// Gestionnaire de fermeture de fenêtre
// int	exit_game(t_data *data)
// {
// 	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
// 	// free_resources(data);
// 	free_all(data, NULL);
// 	exit(0);
// 	return (0);
// }


int    key_press(int keycode, t_data *data)
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
    if (keycode == KEY_LEFT)
        data->movement.rot_left = 1;
    if (keycode == KEY_RIGHT)
        data->movement.rot_right = 1;
    return (0);
}

int    key_release(int keycode, t_data *data)
{
    if (keycode == KEY_W)
        data->movement.forward = 0;
    if (keycode == KEY_S)
        data->movement.backward = 0;
    if (keycode == KEY_A)
        data->movement.left = 0;
    if (keycode == KEY_D)
        data->movement.right = 0;
    if (keycode == KEY_LEFT)
        data->movement.rot_left = 0;
    if (keycode == KEY_RIGHT)
        data->movement.rot_right = 0;
    return (0);
}

int    exit_game(t_data *data)
{
    cleanup_mlx(data);
    free_all(data, NULL);
    exit(0);
    return (0);
}

void    init_hooks(t_data *data)
{
    // Hook pour la fermeture de la fenêtre (croix rouge)
    mlx_hook(data->mlx.win, 17, 0, exit_game, data);
    // Hook pour les touches du clavier (appui)
    mlx_hook(data->mlx.win, 2, 1L<<0, key_press, data);
    // Hook pour les touches du clavier (relâchement)
    mlx_hook(data->mlx.win, 3, 1L<<1, key_release, data);
    // Hook pour le rendu continu
    mlx_loop_hook(data->mlx.mlx, game_loop, data);
}

// void	init_hooks(t_data *data)
// {
// 	mlx_hook(data->mlx.win, 2, 1L << 0, handle_keypress, data);   // Touche pressée
// 	mlx_hook(data->mlx.win, 3, 1L << 1, handle_keyrelease, data); // Touche relâchée
// 	mlx_hook(data->mlx.win, 17, 0, exit_game, data);
// 		// Fermeture fenêtre
// 	mlx_loop_hook(data->mlx.mlx, game_loop, data);                // Boucle de jeu
// }