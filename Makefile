# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 15:59:01 by nfurlani          #+#    #+#              #
#    Updated: 2024/08/27 17:46:05 by nfurlani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3D

SRC     =	./sources/main.c \
			./sources/free.c \
			./sources/free_entities.c \
			./sources/check_map.c \
			./sources/raycasting/raycasting.c \
			./sources/raycasting/calculate_ray.c \
			./sources/rendering/rendering.c \
			./sources/rendering/floor_sky.c \
			./sources/rendering/doors_walls.c \
			./sources/rendering/drawing.c \
			./sources/keys.c \
			./sources/map/check_parameters.c \
			./sources/map/enemies_properties.c \
			./sources/map/get_next_line.c \
			./sources/map/init_entities.c \
			./sources/map/init_parameters.c \
			./sources/map/init_textures.c \
			./sources/map/map.c \
			./sources/map/position.c \
			./sources/enemies/enemies.c \
			./sources/enemies/enemies_utils.c \
			./sources/movement/collision.c \
			./sources/movement/movement.c \
			./sources/movement/rotation.c \
			./sources/elements/dog.c \
			./sources/elements/food.c \
			./sources/elements/door.c \
			./sources/elements/paws.c \
			./sources/elements/health_bar.c \
			./sources/cat/cat.c \
			./sources/cat/visibility.c \
			./sources/cat/cat_direction.c \
			./sources/cat/cat_path.c \
			./sources/entities/entity.c \
			./sources/entities/add_entities.c \
			./sources/entities/draw_entities.c \
			./sources/entities/render_entities.c \
			./sources/entities/attack.c \
			./sources/textures/load_enemy_textures.c \
			./sources/textures/load_textures.c \
			./sources/minimap.c \
			./sources/utils.c \
			./sources/utils2.c \

# ANSI COLOR
RED     = \033[0;31m
BLACK   = \033[1;30m
WHITE   = \033[1;37m
BLUE    = \033[1;34m
YELLOW2 = \033[93;226m
GREEN2  = \033[92;118m
GREEN   = \e[92;5;118m
YELLOW  = \e[93;5;226m
GRAY    = \e[33;2;37m
RESET   = \e[0m
CURSIVE = \e[33;3m

CC = gcc
FLAGS = -Wall -Wextra -Werror

OBJS = $(SRC:.c=.o)

LIBRARY = mlx/
LIBS = -L$(LIBRARY) -lmlx -lX11 -lXext -lm
CCFLAGS = -I$(LIBRARY)

RM = rm -f

.c.o:
	@$(CC) $(CCFLAGS) $(FLAGS) -c $< -o ${<:.c=.o} > /dev/null

$(NAME): ${OBJS}
	@printf "$(CURSIVE)$(YELLOW)  - Compiling minilibx ... $(RESET)\n"
	@make -s -C $(LIBRARY) > /dev/null
	@printf "\e[0m\e[92m - minilibx compiled.$(RESET)\n"
	@printf "$(CURSIVE)$(YELLOW)  - Compiling Cub3D ... $(RESET)\n"
	@$(CC) $(OBJS) $(LIBS) $(FLAGS) -o $(NAME)
	@printf "\e[0m\e[92m - Cub3D compiled.$(RESET)\n"

all: $(NAME)

clean:
	@$(RM) $(OBJS)
	@printf "\e[0m\e[92m$(RED) - OBJS Cub3D removed.$(RESET)\n"

fclean: clean
	@make -s clean -C $(LIBRARY) > /dev/null
	@printf "\e[0m\e[92m$(RED) - library minilibx removed.$(RESET)\n"
	@$(RM) $(NAME)
	@printf "\e[0m\e[92m$(RED) - Cub3D removed.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
