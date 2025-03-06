CC = cc
NAME = minirt
FLAGS = -Wall -Wextra -Werror
SRCS = ./srcs/minirt.c ./srcs/parse.c ./srcs/vexmanip.c
OBJS = ${SRCS:.c=.o}

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@make -s -C libs/libft MAKEFLAGS=-silent
	${CC} ${FLAGS} ${OBJS} -o ${NAME} -L./libs/libft -lft -lm

all: ${NAME}

clean:
	@make clean -s -C libs/libft MAKEFLAGS=-silent
	rm -rf ${OBJS}

fclean: clean
	@make fclean -s -C libs/libft MAKEFLAGS=-silent
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re

