CC = cc
INCLUDES = ./includes/minirt.h ./includes/vex.h ./libs/libft/libft.h
NAME = minirt
FLAGS = -Wall -Wextra -Werror -g
SRCS = ./srcs/vexmanip2.c ./srcs/vexmanip3.c ./srcs/parse3.c ./srcs/parse2.c ./srcs/rot.c ./srcs/cylinder_aux.c ./srcs/trans.c ./srcs/shorteners.c ./srcs/hooksmain.c ./srcs/hooks1.c ./srcs/hooks2.c ./srcs/hooks3.c ./srcs/interloops.c ./srcs/lightapp.c ./srcs/intersections.c ./srcs/hfuncs.c ./srcs/tracing.c ./srcs/minirt.c ./srcs/camera.c ./srcs/parse.c ./srcs/vexmanip.c ./srcs/verifications.c ./srcs/verifications2.c ./srcs/intersection_aux.c ./srcs/intersection_aux2.c ./srcs/lightapp_aux.c
OBJS = ${SRCS:.c=.o}
BLUE = \033[1;36m
RED = \033[1;31m
RESET = \033[0m

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS} ${INCLUDES}
	@make -s -C libs/libft MAKEFLAGS=-silent
	@make -s -C libs/minilibx-linux MAKEFLAGS=-silent
	${CC} ${FLAGS} ${OBJS} -o ${NAME} -L./libs/libft -lft -L./libs/minilibx-linux -lmlx -lXext -lX11 -lm 
	@clear
	@echo "$(BLUE)$(NAME) "is ready to go" $(RESET)"

all: ${NAME}

clean:
	@make clean -s -C libs/libft MAKEFLAGS=-silent
	@make clean -s -C libs/minilibx-linux MAKEFLAGS=-silent
	rm -rf ${OBJS}
	clear
	@echo "$(RED)"Objects cleaned successfully"$(RESET)"

fclean: clean
	@make fclean -s -C libs/libft MAKEFLAGS=-silent
	rm -rf ${NAME}
	clear
	@echo "$(RED)"Objects cleaned successfully"$(RESET)"

re: fclean all

.PHONY: all clean fclean re

