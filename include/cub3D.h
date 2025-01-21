/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:14:56 by fzayani           #+#    #+#             */
/*   Updated: 2025/01/21 11:31:41 by lanani-f         ###   ########.fr       */
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
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define MINIMAP_SIZE 200
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_movement
{
	int				forward;
	int				backward;
	int				left;
	int				right;
	int				rot_left;
	int				rot_right;
	double			move_speed;
	double			rot_speed;
	int				mouse_x;
    int				prev_mouse_x;
}					t_movement;

typedef struct s_draw_section
{
	int				start;
	int				end;
	int				x;
}					t_draw_section;

typedef struct s_floor
{
	double			player_distance;
	int				color;
	double			floor_x;
	double			floor_y;
	double			pos_z;
	double			row_distance;
	int				tex_x;
	int				tex_y;
}					t_floor;

typedef struct s_door
{
	int				x;
	int				y;
	int				is_open;
	double			animation; // Pour l'animation (0.0 à 1.0)
}					t_door;

typedef struct s_keys
{
	int				e;
}					t_keys;

typedef struct s_minimap
{
	double			scale;
	int				width;
	int				height;
	int				offset_x;
	int				offset_y;
}					t_minimap;
typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				player_dir;
	int				count;
}					t_player;

typedef struct s_texture
{
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_texture;

typedef struct s_door_texture
{
	t_texture		frames[8];
	int				num_frames;
}					t_door_texture;

typedef struct s_ray
{
	double			camera_x;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct s_mlx_data
{
	void			*mlx;
	void			*win;
	t_texture		no_tex;
	t_texture		so_tex;
	t_texture		we_tex;
	t_texture		ea_tex;
	t_texture		do_tex;
}					t_mlx_data;

typedef struct s_data
{
	t_player		player;
	char			**map;
	char			**copie_map;
	int				map_width;
	int				map_height;
	void			*texture;
	char			*n_t;
	char			*s_t;
	char			*w_t;
	char			*e_t;
	char			*do_t;
	int				c_color;
	int				f_color;
	int				no_loaded;
	int				so_loaded;
	int				we_loaded;
	int				ea_loaded;
	int				do_loaded;
	int				f_loaded;
	int				c_loaded;
	int				c_is_texture;
	int				f_is_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	char			*no_texture;
	char			*do_texture;
	char			*c_texture;
	char			*f_texture;
	t_mlx_data		mlx;
	t_texture		img;
	t_texture		sky_tex;
	t_texture		floor;
	t_door_texture	door_tex;
	t_movement		movement;
	t_minimap		minimap;
	t_door			*doors;
	t_keys			keys;
	t_ray			ray;
	int				num_doors;
}					t_data;

/// check_extension/cub_extension.c
int					cub_extension(const char *filename);
int					check_arguments(int ac, char **av);

/// map/map_closed.c

int					get_map_dimensions(char **lines, int start_line,
						int *height, int *width);
int					is_space_closed(t_data *data, int y, int x);

/// map/check_map.c

int					check_map_borders(t_data *data);
int					check_space_sequence(t_data *data, int y, int x);

/// map/utils_map.c

int					is_space_at_beginning(t_data *data, int y, int x);
int					is_valid_char(char c);
int					is_map_char(char c);
int					handle_empty_line(char *trimmed);
int					handle_texture_line(char *trimmed, int *f_elements);

// map/player.c

int					check_player(t_data *data);
int					is_valid_map_line(char *line);

// map/map_start.c

int					is_texture_identifier(const char *str);
int					process_line(char **lines, int *i, int *f_elements);

// map/store_map.c

int					store_map(t_data *data, char **lines, int start_line);

// map/utils_store.c

int					get_map_height(char **lines, int start_line);
int					get_adjusted_len(char *line);

/// map/floodfill.c

int					check_map_valid(t_data *data);
int					find_map_start(char **lines);
int					is_valid_map_line(char *line);
int					check_space_sequence(t_data *data, int y, int x);

/// utils/free.c

void				free_map(t_data *data);
void				ft_free_split(char **array);
void				free_lines(char **lines);
void				free_textures(t_data *data);
void				free_all(t_data *data, char **lines);
void				free_textures_3(t_data *data);
void				free_textures_2(t_data *data);

// utils/clean_mlx.c

void				cleanup_mlx(t_data *data);
void				destroy_texture(void *mlx, t_texture *tex);

// utils/errors.c

int					error_exit(const char *message);

/// check_file/parse_file.c

int					parse_color(const char *str);

// check_file/check_path.c

char				*clean_texture_path(const char *path);

// int parse_texture_colors(t_data *data, char **lines);
int					parse_texture_colors(t_data *data, char **lines,
						const char *filename);
void				init_data(t_data *data);
int					parse_texture_line(t_data *data, char *line);
int					check_texture_format(const char *path);
char				*clean_line(char *line);
int					is_valid_identifier(char *line);

/// check_file/parse_texture_color.c

int					validate_color_values(char *str);

/// check_file/check_texture.c

int					no_texture(t_data *data, char *cleaned);
int					do_texture(t_data *data, char *cleaned);
int					so_texture(t_data *data, char *cleaned);
int					check_ea_texture(t_data *data, char *cleaned);
int					check_we_texture(t_data *data, char *cleaned);

/// check_file/check_texture_2.c

int					ea_we_tex(t_data *data, char *cleaned, int is_east);
int					handle_floor_texture(t_data *data, char *cleaned);
int					check_floor_color(t_data *data, char *cleaned);
int					check_floor_element(t_data *data, char *cleaned);
int					handle_ceiling_texture(t_data *data, char *cleaned);

// check_file/utils_file.c

int					ft_arraylen(char **array);
char				*ft_strtrim2(const char *str);

////check_file/check_valid_data_6elements.c

int					is_valid_texture_path(const char *path);
int					is_valid_color_format(const char *str);

// mlx/init_mlx.c

int					init_mlx(t_data *data);
int					load_texture(t_data *data, t_texture *tex, char *path);
int					load_textures(t_data *data);
int					init_game(t_data *data);
int					validate_game_data(t_data *data);

// mlx/init_image.c

int					init_image_addr(t_data *data);
int					init_mlx_window(t_data *data);

// mlc/init_hooks.c

int					handle_mouse(int x, int y, t_data *data);
void				init_hooks(t_data *data);
int					exit_game(t_data *data);
int					key_press(int keycode, t_data *data);
int					key_release(int keycode, t_data *data);

// mlx/draw_map.c

void				draw_background(t_data *data);
int					render(t_data *data);

// raycasting/raycasting.c

void				init_player_pos(t_ray *ray, t_data *data);
void				raycasting(t_data *data);
int					game_loop(t_data *data);
int					get_texture_color(t_data *data, t_ray *ray, int y);
void				init_ray_dir(t_ray *ray, t_data *data, int x);
void				init_ray_dist(t_ray *ray);
void				init_ray_step(t_ray *ray);
void				perform_dda(t_ray *ray, t_data *data);
void				calculate_wall_dist(t_ray *ray);
void				calculate_line_height(t_ray *ray);
void				init_ray_position(t_ray *ray, t_data *data);
void				init_movement_values(t_data *data);
int					apply_lighting(int color, double distance);
void				init_movement_values(t_data *data);

// raycasting/perform_dda_2.c

void				update_ray_position(t_ray *ray);
int					check_wall_collision(t_ray *ray, t_data *data);

// raycasting/position.c

void				set_direction_north(t_ray *ray);
void				set_direction_vectors_(t_ray *ray, char dir);
void				update_player_vectors(t_ray *ray, t_data *data);
void				init_player_pos(t_ray *ray, t_data *data);
void				calculate_texture_coords(t_floor *floor, t_data *data,
						int x, int y);

// raycasting/floor.c

void				init_floor_values(t_floor *floor, t_data *data, int x,
						int y);
int					get_floor_color(t_floor *floor, t_data *data);
void				draw_floor(t_data *data, int x, int y);

// raycasting/get.c

int					get_tex_x(t_texture *texture, t_ray *ray);
int					get_tex_color(t_texture *texture, int tex_x, int tex_y);
int					get_wall_x(t_ray *ray, double *wall_x);
int					get_tex_x_(t_ray *ray, t_texture *texture, double wall_x);
int					get_tex_y_(t_ray *ray, t_texture *texture, int y);

// raycasting/draw.c

void				draw_vertical_line(t_data *data, t_ray *ray, int x);
void				draw_sky(t_data *data, t_ray *ray, int x, int y);
void				draw_wall(t_data *data, t_ray *ray, int x, int y);
void				draw_section(t_data *data, t_ray *ray, t_draw_section *ds);

// minimap

void				init_minimap(t_data *data);
void				draw_minimap(t_data *data);
void				draw_map_content(t_data *data);
void				draw_player_on_map(t_data *data);
void				put_minimap_pixel(t_data *data, int x, int y, int color);
int					is_valid_player_char(char c);
void				put_pixel_minimap(t_data *data, int x, int y, int color);

// contols/player_mouvement.c

void				handle_forward_movement(t_data *data);
void				handle_strafe_movement(t_data *data);
void				handle_rotation_left(t_data *data);

// contols/utils.c

double				adjust_speed(t_data *data);
void				update_player_pos(t_data *data, double move_x,
						double move_y);
void				update_strafe_pos(t_data *data, double move_x,
						double move_y);
double				adjust_strafe_speed(t_data *data);
int					is_door_closed(t_data *data, int x, int y);

// contols/player_ro_utils.c

void				rotate_vectors(t_data *data, double angle);
void				update_ray_vectors(t_data *data);
void				move_left(t_data *data, double move_speed);
void				move_right(t_data *data, double move_speed);

// rotation

void				handle_rotation(t_data *data);

// doors

int					init_doors(t_data *data);
void				handle_door(t_data *data);
void				update_doors(t_data *data);
int					load_door_textures(t_data *data);

// doors/utils.c

void				count_door_in_row(t_data *data, int i, int j, int *count);
void				count_doors_recursive(t_data *data, int i, int *count);
void				init_door(t_door *door, int x, int y);
void				fill_door_in_row(t_data *data, int i, int j, int *count);
void				fill_doors_recursive(t_data *data, int i, int *count);

// vectors

void				set_direction_vectors(t_ray *ray, char dir);

// minimap/minimap_utils.c

int					is_valid_map_char(char c);

#endif