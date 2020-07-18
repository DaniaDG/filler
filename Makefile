# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/25 14:23:51 by bsausage          #+#    #+#              #
#    Updated: 2020/07/18 13:40:04 by Alkor            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsausage.filler
NAME_VIZ = visualizer

CC = gcc 
FLAGS = -Wextra -Wall -Werror -g
LIBRARIES = -lm -lft -L$(LIBFT_DIRECTORY)
MLX_LIBRARIES = -lmlx -lm -L$(MINILIBX_DIRECTORY) -framework OpenGL -framework AppKit
INCLUDES = -I $(LIBFT_HEADERS_DIRECTORY) -I $(HEADERS_DIRECTORY) -I$(MINILIBX_HEADERS)

# LIBFT
LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = libft/
LIBFT_HEADERS_DIRECTORY = $(LIBFT_DIRECTORY)includes/

# MINILIBX
MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
MINILIBX_DIRECTORY = ./minilibx_macos/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

HEADERS_LIST = filler.h vis.h
HEADERS_DIRECTORY = includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = sources/
SOURCES_LIST = get_data_1.c get_data_2.c init.c list.c heat_map.c solve.c\
free_functions.c
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

#FILLER_PLAYER

F_SOURCES_DIRECTORY = sources/
F_SOURCES_LIST = main.c 
F_SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(F_SOURCES_LIST))

F_OBJECTS_LIST = $(patsubst %.c, %.o, $(F_SOURCES_LIST))
F_OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(F_OBJECTS_LIST))

#VIZUALIZER

VIZ_SOURCES_DIRECTORY = sources/
VIZ_SOURCES_LIST = main_vizualizer.c init_mlx.c put_pixel.c rgb.c threads.c drawing.c
VIZ_SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(VIZ_SOURCES_LIST))

VIZ_OBJECTS_LIST = $(patsubst %.c, %.o, $(VIZ_SOURCES_LIST))
VIZ_OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(VIZ_OBJECTS_LIST))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME) $(NAME_VIZ)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS) $(F_OBJECTS) $(LIBFT)
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) $(F_OBJECTS) $(LIBRARIES) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(NAME_VIZ): $(LIBFT) $(MINILIBX) $(OBJECTS_DIRECTORY) $(OBJECTS) $(VIZ_OBJECTS)
	@$(CC) $(FLAGS) $(MLX_LIBRARIES) $(LIBRARIES) $(INCLUDES) $(OBJECTS) $(VIZ_OBJECTS) -o $(NAME_VIZ)
	@echo "\n$(NAME_VIZ): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME_VIZ): $(GREEN)$(NAME_VIZ) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(MINILIBX):
	@echo "$(MINILIBX): $(GREEN)Creating $(MINILIBX)...$(RESET)"
	@$(MAKE) -sC $(MINILIBX_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(MINILIBX)
	@echo "$(MINILIBX): $(RED)$(MINILIBX) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
