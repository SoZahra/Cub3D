# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 15:05:07 by fzayani           #+#    #+#              #
#    Updated: 2025/01/21 11:41:17 by fzayani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
BLUE_LIGHTER = \033[38;5;123m
BLUE_LIGHT = \033[36m
BLUE = \033[34m
BLUE_LIGHTER_DARK = \033[38;5;32m
BLUE_DARK = \033[38;5;24m
RESET = \033[0m

# Program name
NAME = cub3D

# Directories
SRC_PATH 	= src/
CHECK_EXTENSION_DIR = $(SRC_PATH)check_extension/
CHECK_FILE 	= $(SRC_PATH)check_file/
CONTROLS 	= $(SRC_PATH)controls/
DATA	 	= $(SRC_PATH)data/
DOORS		= $(SRC_PATH)doors/
MAP			= $(SRC_PATH)map/
MLX			= $(SRC_PATH)mlx/
UTILS		= $(SRC_PATH)utils/
MINIMAP		= $(SRC_PATH)minimap/
RAYCASTING	= $(SRC_PATH)raycasting/

CHECK_EXTENSION_DIR = cub_extension.c
CHECK_FILE = parse_file.c utils_file.c check_path.c textures.c texture_color.c check_textures.c check_texture_2.c
CONTROLS = key_events.c player_movement.c player_rotation.c utils.c player_ro_utils.c
DATA = init.c
MLX = init_mlx.c draw_map.c init_hooks.c init_image.c
DOORS = init_doors.c utils.c
UTILS = errors.c free.c free_2.c clean_mlx.c
RAYCASTING = raycasting.c init_ray.c perform_dda.c vectors.c position.c perform_dda_2.c floor.c get.c draw.c
MINIMAP = check_minimap.c minimap_player.c minimap_utils.c minimap.c
MAP = check_map.c floodfill.c utils_map.c map_closed.c player.c map_start.c store_map.c utils_store.c

SRCS_FILES = main.c \
			$(addprefix check_extension/, $(CHECK_EXTENSION_DIR)) \
			$(addprefix check_file/, $(CHECK_FILE)) \
			$(addprefix controls/, $(CONTROLS)) \
			$(addprefix data/, $(DATA)) \
			$(addprefix doors/, $(DOORS)) \
			$(addprefix map/, $(MAP)) \
			$(addprefix mlx/, $(MLX)) \
			$(addprefix utils/, $(UTILS)) \
			$(addprefix minimap/, $(MINIMAP)) \
			$(addprefix raycasting/, $(RAYCASTING))

SRCS = $(addprefix $(SRC_PATH), $(SRCS_FILES))

# Object files
OBJS_PATH = .objs/
OBJS = $(SRCS:$(SRC_PATH)%.c=$(OBJS_PATH)%.o)

# Libraries and includes
INC_PATH = include/
LIBFT_PATH = ./libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a
MLX_PATH = ./mlx/
MLX_LIB = $(MLX_PATH)libmlx_Linux.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(INC_PATH) -I$(LIBFT_PATH) -I$(MLX_PATH) -g
LFLAGS = -L$(LIBFT_PATH) -lft -L$(MLX_PATH) -lmlx_Linux -lXext -lX11 -lm -lbsd
RM = rm -rf

# Rules
all: $(NAME)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	@echo "$(BLUE_LIGHTER)╔═════════════════════════════════════════╗$(RESET)"
	@echo "$(BLUE_LIGHTER)║           Compiling $(NAME)...            ║$(RESET)"
	@$(CC) $(OBJS) $(LFLAGS) -o $(NAME)
	@echo "$(BLUE_LIGHTER)║  $(NAME) has been created successfully!   ║$(RESET)"
	@echo "$(BLUE_LIGHTER)╚═════════════════════════════════════════╝$(RESET)"

# Object files compilation
$(OBJS_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Libraries compilation
$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

$(MLX_LIB):
	@make -C $(MLX_PATH)

clean:
	$(RM) $(OBJS_PATH)
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(MLX_PATH)
	@echo "$(BLUE_LIGHTER_DARK)🧹 Cleaning object files...$(RESET)"

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "$(BLUE_DARK)🗑️  Removing $(NAME)...$(RESET)"

re: fclean all
	@echo "$(BLUE_DARK)📚 $(NAME) recompiled!$(RESET)"

.PHONY: all clean fclean re