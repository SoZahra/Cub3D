/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:14:56 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/10 15:14:40 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "fcntl.h"
# include "math.h"
# include "stdio.h"
# include "unistd.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <limits.h>
# include <string.h>

# define MAX_LINES 1000

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

// structure donnees de la map
typedef struct s_data
{
	t_player	player;
	void		*mlx;
	void		*win;
	char		**map;
	char		**copie_map;
	int			map_width;
	int			map_height;
	void		*texture;
	char		*n_t;
	char		*s_t;
	char		*w_t;
	char		*e_t;
	int			c_color;
	int			f_color;
	int			no_loaded;
	int			so_loaded;
	int			we_loaded;
	int			ea_loaded;
	int			f_loaded;
	int			c_loaded;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	char		*no_texture;
}				t_data;

/// parsing/parsing.c

/// check_extension/cub_extension.c
int				cub_extension(const char *filename);
int				check_arguments(int ac, char **av);

///map/map_closed.c

int	get_map_dimensions(char **lines, int start_line, int *height, int *width);
int	is_space_closed(t_data *data, int y, int x);

/// map/check_map.c

int	check_map_borders(t_data *data);
int	check_space_sequence(t_data *data, int y, int x);

///map/utils_map.c

int	is_space_at_beginning(t_data *data, int y, int x);
int	is_valid_char(char c);
int	is_map_char(char c);
int	handle_empty_line(char *trimmed);
int	handle_texture_line(char *trimmed, int *f_elements);

//map/player.c

int	check_player(t_data *data);
int	is_valid_map_line(char *line);

//map/map_start.c

int is_texture_identifier(const char *str);
int	process_line(char **lines, int *i, int *f_elements);

//map/store_map.c

int				store_map(t_data *data, char **lines, int start_line);

//map/utils_store.c

int	get_map_height(char **lines, int start_line);
int	get_adjusted_len(char *line);

/// map/floodfill.c

int				check_map_valid(t_data *data);
int				find_map_start(char **lines);
int				is_valid_map_line(char *line);
int	check_space_sequence(t_data *data, int y, int x);

/// utils/free.c

void			free_map(t_data *data);
void			ft_free_split(char **array);
void			free_lines(char **lines);

// utils/errors.c

void			error_exit(const char *message);

/// check_file/parse_file.c

int	parse_color(const char *str);

// int parse_texture_colors(t_data *data, char **lines);
int				parse_texture_colors(t_data *data, char **lines,
					const char *filename);
void			init_data(t_data *data);
int				parse_texture_line(t_data *data, char *line);
int				check_texture_format(const char *path);
char			*clean_line(char *line);
int				is_valid_identifier(char *line);

/// check_file/parse_texture_color.c

int	validate_color_values(char *str);

// check_file/utils_file.c

int				ft_arraylen(char **array);
char			*ft_strtrim2(const char *str);

////check_file/check_valid_data_6elements.c

int				is_valid_texture_path(const char *path);
int				is_valid_color_format(const char *str);

#endif