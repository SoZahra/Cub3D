# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 15:05:07 by fzayani           #+#    #+#              #
#    Updated: 2025/01/14 14:02:15 by fzayani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC_PATH            =   src/
PARSING_DIR         =   $(SRC_PATH)parsing
CHECK_EXTENSION_DIR =   $(SRC_PATH)check_extension
MAP_DIR             =   $(SRC_PATH)map

SRCS_FILES  =   main.c \
                parsing/parsing.c parsing/utils_parsing.c \
                check_extension/cub_extension.c \
				check_file/parse_file.c check_file/utils_file.c check_file/check_path.c check_file/textures.c check_file/texture_color.c \
                map/check_map.c map/floodfill.c  map/utils_map.c  map/map_closed.c map/player.c map/map_start.c map/store_map.c map/utils_store.c\
				mlx/init_mlx.c mlx/draw_map.c mlx/init_hooks.c \
				utils/errors.c utils/free.c utils/clean_mlx.c \
				doors/init_doors.c \
				minimap/check_minimap.c minimap/minimap_player.c minimap/minimap_utils.c minimap/minimap.c \
				raycasting/raycasting.c raycasting/init_ray.c raycasting/perform_dda.c raycasting/vectors.c \
				controls/key_events.c controls/player_movement.c controls/player_rotation.c

SRCS        =   $(addprefix $(SRC_PATH), $(SRCS_FILES))
# OBJS		=	$(addprefix $(OBJS_PATH), $(SRCS:.c=.o))
# INC			=	$(addprefix $(INC_PATH), $(INC_FILE))

# Fichiers objets générés dans le dossier .objs/
OBJS_PATH   =   .objs/
OBJS        =   $(SRCS:$(SRC_PATH)%.c=$(OBJS_PATH)%.o)

# Include et libft
INC_PATH    =   include/
LIBFT_PATH  =   ./libft/
LIBFT_LIB   =   $(LIBFT_PATH)libft.a

MLX_PATH	=	./mlx/
MLX_LIB		=	$(MLX_PATH)libmlx_Linux.a

# Compilation
CC          =   cc
CFLAGS      =   -Wall -Werror -Wextra -I$(INC_PATH) -I$(LIBFT_PATH) -g
LFLAGS      =   -L$(LIBFT_PATH) -lft -L$(MLX_PATH) -lmlx_Linux -lXext -lX11 -lm -lbsd -lft
RM          =   rm -rf

# Couleurs
GREEN       =   \033[32m
YELLOW      =   \033[33m
RED         =   \033[31m
RESET       =   \033[0m

# Règle principale
all:    $(NAME)

$(NAME):    $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	@echo "$$BANNER"
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
	@echo "$(GREEN)[DONE] CUB3D compiled!$(RESET)"

# Compilation des fichiers .c en .o dans .objs/
$(OBJS_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@) # Crée le sous-dossier si nécessaire
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)Compiling: $<$(RESET)"

# Compilation de la libft
$(LIBFT_LIB):
	@make -C $(LIBFT_PATH) --silent

$(MLX_LIB):
	@make -C $(MLX_PATH) --silent

# Nettoyage des objets
clean:
	$(RM) $(OBJS_PATH)
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(MLX_PATH)
	@echo "$(RED)[DONE] Objects files deleted...$(RESET)"

# Nettoyage complet
fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "$(RED)[DONE] CUB3D deleted...$(RESET)"

define BANNER
$(RED)
 ██████╗ ██████╗ ██████╗ ██████╗ ██████╗
██╔════╝██╔═══██╗██╔══██╗╚════██╗██╔══██╗
██║     ██║   ██║██████╔╝ █████╔╝██║  ██║
██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║
╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝
 ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝
$(RESET)
endef
export BANNER

# Recompilation complète
re: fclean all
	@echo "$(GREEN)[DONE] CUB3D recompiled!$(RESET)"

.PHONY: all clean fclean re
