NAME	= cub3d

SRC		= ./sources/main.c ./sources/raycasting.c ./sources/map.c ./sources/rendering.c ./sources/drawing.c ./sources/get_next_line.c

#ANSII COLOR

RED		= \033[0;31m
BLACK	= \033[1;30m
WHITE	= \033[1;37m
BLUE	= \033[1;34m
YELLOW2  = \033[93;226m
GREEN2   = \033[92;118m
GREEN   = \e[92;5;118m
YELLOW  = \e[93;5;226m
GRAY    = \e[33;2;37m
RESET   = \e[0m
CURSIVE = \e[33;3m

CC = gcc 
FLAG = -Werror -Wextra - Wall -g

OBJS = $(SRC:.c=.o)

LIBRARY = mlx/
LIBS = -L$(LIBRARY) -lmlx -framework OpenGL -framework AppKit $(LIBRARY)libmlx.a
CCFLAGS = -I$(LIBRARY)
# LIBS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

RM = rm -f

CC = gcc -Wall -Wextra -Werror -g

.c.o:
	@${CC} $(CCFLAGS) -c $< -o ${<:.c=.o} > /dev/null

$(NAME): ${OBJS}
	@printf "$(CURSIVE)$(YELLOW) 	- Compiling minilibx ... $(RESET)\n"
	@make -s -C $(LIBRARY) > /dev/null
	@printf "\e[0m\e[92m - minilibx compiled.$(RESET)\n"
	@printf "$(CURSIVE)$(YELLOW) 	- Compiling Cub3D ... $(RESET)\n"
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@printf "\e[0m\e[92m - Cub3D compiled.$(RESET)\n"

all: $(NAME)

clean:
	@${RM} $(OBJS)
	@printf "\e[0m\e[92m$(RED) - OBJS Cub3D removed.$(RESET)\n"

fclean: clean
	@make -s clean -C $(LIBRARY) > /dev/null
	@printf "\e[0m\e[92m$(RED) - library minilibx removed.$(RESET)\n"
	@${RM} $(NAME) ${OBJB}
	@printf "\e[0m\e[92m$(RED) - Cub3D removed.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re