/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:14:56 by fzayani           #+#    #+#             */
/*   Updated: 2024/11/08 16:20:17 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "math.h"
# include "stdio.h"
# include "unistd.h"
# include "fcntl.h"
# include <string.h>
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

#define MAX_LINES 1000

typedef struct s_player
{
	int			player_x;
	int			player_y;
	int			player_dir;
	int			p_n;
	int			p_s;
	int			p_e;
	int			p_w;
	int			cc;
	int			count;
}				t_player;

//structure donnees de la map
typedef struct s_data
{
	// t_img		*img;
	t_player	player;
	void		*mlx;
	void		*win;
	char		**map;
	char		**copie_map;
	int			map_width;
	int			map_height;
	void		*texture;
	char 		*n_t;
	char 		*s_t;
	char 		*w_t;
	char 		*e_t;
	int 		f_color;
	int			c_color;
	int			no_loaded; // flag pour NO chargé
	int			so_loaded; // flag pour SO chargé
	int			we_loaded; // flag pour WE chargé
	int			ea_loaded; // flag pour EA chargé
	int			f_loaded;  // flag pour F chargé
	int			c_loaded;  // flag pour C chargé
	char *so_texture;
    char *we_texture;
    char *ea_texture;
    char *no_texture;
}				t_data;

///parsing/parsing.c
void	count_map_elements(t_data *data, int *exit_count, int *start_count,
		int *collectible_count);
int	check_map_elements(t_data *data);
void	check_invalid_characters(t_data *data, char element);

///check_extension/cub_extension.c
int	cub_extension(const char *filename);
int	check_arguments(int ac, char **av);

///map/check_map.c
int	check_map_walls(t_data *data);
void	check_map(t_data *data);

///utils/free.c

void	free_map(t_data *data);
void	ft_free_split(char **array);

//utils/errors.c

void	error_exit(const char *message);


///check_file/parse_file.c

// int parse_texture_colors(t_data *data, char **lines);
int parse_texture_colors(t_data *data, char **lines, const char *filename);
int parse_cub(t_data *data, const char *filename);
int	parse_color(const char *line);
int parse_map(t_data *data, char **lines);
int validate_map(t_data *data, char **lines, int map_start);

void	init_texture_colors_flags(t_data *data);
int	verify_texture_and_colors(t_data *data);
int	parse_texture_line(t_data *data, char *line);
int	compare_loaded(t_data *data, char *line);
void init_data(t_data *data);
int parse_cub(t_data *data, const char *filename);
int check_for_duplicates(t_data *data, const char *line);

//check_file/utils_file.c

int	ft_arraylen(char **array);
int is_empty_line(const char *line);

////check_file/check_valid_data_6elements.c

int is_valid_texture_path(const char *path);
int is_valid_color_format(const char *str);

#endif