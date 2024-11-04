/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:14:56 by fzayani           #+#    #+#             */
/*   Updated: 2024/11/04 11:59:02 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "math.h"
# include "stdio.h"
# include "unistd.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>


typedef struct s_player
{
	int			x;
	int			y;
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

//utils/errors.c

void	error_exit(const char *message);


#endif