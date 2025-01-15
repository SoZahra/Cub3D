/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:41:34 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/15 13:50:41 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// void	init_data(t_data *data)
// {
// 	// Initialisation basique
// 	data->mlx.mlx = NULL;
// 	data->mlx.win = NULL;
// 	data->map = NULL;
// 	data->copie_map = NULL;
// 	data->map_width = 0;
// 	data->map_height = 0;
// 	// textures
// 	data->no_texture = NULL;
// 	data->so_texture = NULL;
// 	data->we_texture = NULL;
// 	data->ea_texture = NULL;
// 	// couleurs
// 	data->f_color = -1;
// 	data->c_color = -1;
// 	// joueur
// 	data->player.pos_x = 0;
// 	data->player.pos_y = 0;
// 	data->player.dir_x = 0;
// 	data->player.dir_y = 0;
// 	data->player.player_dir = 0;
// 	data->player.plane_x = 0;
// 	data->player.plane_y = 0;
// 	// mouvements
// 	data->movement.forward = 0;
// 	data->movement.backward = 0;
// 	data->movement.left = 0;
// 	data->movement.right = 0;
// 	data->movement.rot_left = 0;
// 	data->movement.rot_right = 0;
// 	data->movement.move_speed = 0.05;
// 	data->movement.rot_speed = 0.03;
// 	data->img.img = NULL;
// 	data->img.addr = NULL;
// }

void init_data(t_data *data)
{
    ft_memset(data, 0, sizeof(t_data));  // Initialise tout à 0

    // Puis définir les valeurs spécifiques non-nulles
    data->f_color = -1;
    data->c_color = -1;
    data->movement.move_speed = 0.1;
    data->movement.rot_speed = 0.05;
}

void    init_minimap(t_data *data)
{
    int    max_dim;

    max_dim = data->map_width;
    if (data->map_height > max_dim)
        max_dim = data->map_height;
    data->minimap.scale = MINIMAP_SIZE / max_dim;
    if (data->minimap.scale < 2)
        data->minimap.scale = 2;
    data->minimap.width = data->map_width * data->minimap.scale;
    data->minimap.height = data->map_height * data->minimap.scale;
    data->minimap.offset_x = 10;
    data->minimap.offset_y = WIN_HEIGHT - data->minimap.height - 10;
}

int	init_game(t_data *data)
{
    t_ray initial_ray;

	if (!init_mlx(data))
		return (0);
	if (!check_player(data))
	{
		cleanup_mlx(data);
		return (0);
	}
	if (!load_textures(data))
	{
		cleanup_mlx(data);
		return (0);
	}
    if (!init_doors(data))
	{
		cleanup_mlx(data);
		return (0);
	}
	init_minimap(data);
    init_player_pos(&initial_ray, data);
	init_hooks(data);
	raycasting(data);
	return (1);
}

// int	init_mlx(t_data *data)
// {
// 	data->mlx.mlx = mlx_init();
// 	if (!data->mlx.mlx)
// 		return (error_exit("Failed to init MLX"), 0);
// 	data->mlx.win = mlx_new_window(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT,
// 			"Cub3D");
// 	if (!data->mlx.win)
// 	{
// 		mlx_destroy_display(data->mlx.mlx);
// 		free(data->mlx.mlx);
// 		return (error_exit("Failed to create window"), 0);
// 	}
// 	// Initialiser l'image pour le raycasting
// 	data->img.img = mlx_new_image(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
// 	if (!data->img.img)
// 	{
// 		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
// 		mlx_destroy_display(data->mlx.mlx);
// 		free(data->mlx.mlx);
// 		return (error_exit("Failed to create image"), 0);
// 	}
// 	data->img.addr = (int *)mlx_get_data_addr(data->img.img,
//                                   &data->img.bits_per_pixel,
//                                   &data->img.line_length,
//                                   &data->img.endian);
// 	return (1);
// }

int init_mlx(t_data *data)
{
    data->mlx.mlx = mlx_init();
    if (!data->mlx.mlx)
        return (error_exit("Failed to init MLX"), 0);
    data->mlx.win = mlx_new_window(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    if (!data->mlx.win)
    {
        mlx_destroy_display(data->mlx.mlx);
        free(data->mlx.mlx);
        return (error_exit("Failed to create window"), 0);
    }
    int bits_per_pixel;
    int line_length;
    int endian;
    data->img.img = mlx_new_image(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!data->img.img)
    {
        mlx_destroy_window(data->mlx.mlx, data->mlx.win);
        mlx_destroy_display(data->mlx.mlx);
        free(data->mlx.mlx);
        return (error_exit("Failed to create image"), 0);
    }
    data->img.addr = (int *)mlx_get_data_addr(data->img.img,
                                             &bits_per_pixel,
                                             &line_length,
                                             &endian);
    if (!data->img.addr)
    {
        mlx_destroy_image(data->mlx.mlx, data->img.img);
        mlx_destroy_window(data->mlx.mlx, data->mlx.win);
        mlx_destroy_display(data->mlx.mlx);
        free(data->mlx.mlx);
        return (error_exit("Failed to get image address"), 0);
    }
    data->img.bits_per_pixel = bits_per_pixel;
    data->img.line_length = line_length;
    data->img.endian = endian;
    data->img.width = WIN_WIDTH;
    data->img.height = WIN_HEIGHT;

    return (1);
}

void	check_textures_loaded(t_data *data)
{
	if (!data->mlx.no_tex.img || !data->mlx.so_tex.img || !data->mlx.we_tex.img
		|| !data->mlx.ea_tex.img)
	{
		cleanup_mlx(data);
		error_exit("Failed to load textures");
	}
}

// int load_texture(t_data *data, t_texture *tex, char *path)
// {
// 	tex->img = mlx_xpm_file_to_image(data->mlx.mlx, path, &tex->width,
//			&tex->height);
// 	if(!tex->img)
// 		return(0);
// 	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
//			&tex->line_length, &tex->endian);
// 	if(!tex->addr)
// 		return(0);
// 	return(1);
// }

// int    load_textures(t_data *data)
// {
//     if (!load_texture(data, &data->mlx.no_tex, data->no_texture))
//         return (error_exit("Failed to load NO texture"), 0);
//     if (!load_texture(data, &data->mlx.so_tex, data->so_texture))
//         return (error_exit("Failed to load SO texture"), 0);
//     if (!load_texture(data, &data->mlx.we_tex, data->we_texture))
//         return (error_exit("Failed to load WE texture"), 0);
//     if (!load_texture(data, &data->mlx.ea_tex, data->ea_texture))
//         return (error_exit("Failed to load EA texture"), 0);
//     return (1);
// }

// int	load_texture(t_data *data, t_texture *tex, char *path)
// {
// 	printf("DEBUG: Trying to load texture from path: [%s]\n", path);
// 	if (!path)
// 	{
// 		printf("DEBUG: Path is NULL\n");
// 		return (0);
// 	}
// 	// Vérifier si le fichier existe
// 	if (access(path, F_OK) != 0)
// 	{
// 		printf("DEBUG: File does not exist: %s\n", path);
// 		return (0);
// 	}
// 	// Vérifier si on peut lire le fichier
// 	if (access(path, R_OK) != 0)
// 	{
// 		printf("DEBUG: File is not readable: %s\n", path);
// 		return (0);
// 	}
// 	tex->img = mlx_xpm_file_to_image(data->mlx.mlx, path, &tex->width,
// 			&tex->height);
// 	if (!tex->img)
// 	{
// 		printf("DEBUG: mlx_xpm_file_to_image failed for: %s\n", path);
// 		return (0);
// 	}
// 	printf("DEBUG: Successfully loaded image, getting data address\n");
// 	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
// 			&tex->line_length, &tex->endian);
// 	if (!tex->addr)
// 	{
// 		printf("DEBUG: mlx_get_data_addr failed\n");
// 		return (0);
// 	}
// 	printf("DEBUG: Successfully loaded texture from: %s\n", path);
// 	return (1);
// }

int load_texture(t_data *data, t_texture *tex, char *path)
{
    if (!path || !tex)
        return (0);

    tex->img = mlx_xpm_file_to_image(data->mlx.mlx, path, &tex->width, &tex->height);
    if (!tex->img)
        return (0);

    tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
            &tex->line_length, &tex->endian);
    if (!tex->addr)
    {
        mlx_destroy_image(data->mlx.mlx, tex->img);
        tex->img = NULL;
        return (0);
    }

    // Vérification des dimensions
    if (tex->width <= 0 || tex->height <= 0)
    {
        mlx_destroy_image(data->mlx.mlx, tex->img);
        tex->img = NULL;
        return (0);
    }

    return (1);
}

int	load_textures(t_data *data)
{

	if (!load_texture(data, &data->mlx.no_tex, data->no_texture))
		return (error_exit("Failed to load NO texture"), 0);
	if (!load_texture(data, &data->mlx.so_tex, data->so_texture))
		return (error_exit("Failed to load SO texture"), 0);
	if (!load_texture(data, &data->mlx.we_tex, data->we_texture))
		return (error_exit("Failed to load WE texture"), 0);
	if (!load_texture(data, &data->mlx.ea_tex, data->ea_texture))
		return (error_exit("Failed to load EA texture"), 0);
    if (!load_texture(data, &data->mlx.do_tex, data->do_texture))
		return (error_exit("Failed to load DO texture"), 0);
	if (data->c_is_texture && !load_texture(data, &data->sky_tex, data->c_texture))
		return (error_exit("Failed to load SKY texture"), 0);
	// printf("DEBUG: All textures loaded successfully\n");
	return (1);
}
