/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:17:53 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/13 14:11:08 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void    destroy_texture(void *mlx, t_texture *tex)
{
    if (tex && tex->img)
    {
        mlx_destroy_image(mlx, tex->img);
        tex->img = NULL;
        tex->addr = NULL;
    }
}

void    cleanup_mlx(t_data *data)
{
    if (!data->mlx.mlx)
        return;

    // Destruction des textures
    destroy_texture(data->mlx.mlx, &data->mlx.no_tex);
    destroy_texture(data->mlx.mlx, &data->mlx.so_tex);
    destroy_texture(data->mlx.mlx, &data->mlx.we_tex);
    destroy_texture(data->mlx.mlx, &data->mlx.ea_tex);

    // Destruction de la fenêtre si elle existe
    if (data->mlx.win)
    {
        mlx_destroy_window(data->mlx.mlx, data->mlx.win);
        data->mlx.win = NULL;
    }

    // Destruction du display MLX
    mlx_destroy_display(data->mlx.mlx);
    free(data->mlx.mlx);
    data->mlx.mlx = NULL;
}
