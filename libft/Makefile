# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 16:32:06 by fzayani           #+#    #+#              #
#    Updated: 2024/10/23 14:26:09 by fzayani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAG = -Wall -Wextra -Werror

NAME = libft.a

CC = cc

SRC = ft_atoi.c \
	  ft_bzero.c \
	  ft_isalnum.c \
	  ft_isalpha.c \
	  ft_isascii.c \
	  ft_isdigit.c \
	  ft_isprint.c \
	  ft_itoa.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_memset.c \
	  ft_putchar_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_putstr_fd.c \
	  ft_strchr.c \
	  ft_strdup.c \
	  ft_striteri.c \
	  ft_strjoin.c \
	  ft_strlcat.c \
	  ft_strlen.c \
	  ft_strmapi.c \
	  ft_strncmp.c \
	  ft_substr.c \
	  ft_strnstr.c \
	  ft_strrchr.c \
	  ft_strlcpy.c \
	  ft_calloc.c \
	  ft_split.c \
	  ft_strtrim.c \
	  ft_tolower.c \
	  ft_toupper.c \
	  get_next_line.c \
	  get_next_line_utils.c \
	  ft_print_decim.c \
	  ft_printf.c \
	  ft_print_hex.c \
	  ft_print_p.c \
	  ft_print_str.c \
	  ft_single_chara.c\
	  ft_isspace.c\
	  ft_printf_fd.c\
	  ft_printf_utils.c\
	  ft_itoa_unsig.c\
	  ft_strcmp.c\
	  ft_strndup.c\
	  ft_strncpy.c


src_bonus = ft_lstnew_bonus.c \
	  		ft_lstadd_front_bonus.c \
			ft_lstadd_back_bonus.c \
	  		ft_lstsize_bonus.c \
	  		ft_lstlast_bonus.c \
	  		ft_lstdelone_bonus.c \
	  		ft_lstclear_bonus.c \
	  		ft_lstiter_bonus.c \
	  		ft_lstmap_bonus.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(src_bonus:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(NAME) created"
	@echo "$(NAME) indexed"

bonus: $(NAME) $(OBJ_BONUS)
	@ar rcs $(NAME) $(OBJ_BONUS)
	@echo "$(NAME) created bonus"
	@echo "$(NAME) indexed bonus"

%.o: %.c
	@cc $(FLAG) -c $< -o $@

bonus:

clean:
	@rm -f $(OBJ) $(OBJ_BONUS)
	@echo "OBJ deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) deleted"

re: fclean all

.PHONY: all, clean, fclean, re