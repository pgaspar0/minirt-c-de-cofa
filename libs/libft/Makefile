CC = cc

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

SRCS = ft_atod.c ft_strcmp.c ft_strcpys.c ft_isspace.c free_matrix.c ft_atoi.c ft_atoi_base.c ft_atol.c ft_itoa.c ft_putnbr_fd.c ft_strlcpy.c ft_tolower.c ft_bzero.c ft_memchr.c	ft_putstr_fd.c ft_strlen.c ft_toupper.c ft_calloc.c ft_memcmp.c ft_split.c ft_strmapi.c ft_isalnum.c ft_memcpy.c ft_strchr.c ft_strncmp.c ft_isalpha.c ft_memmove.c ft_strdup.c ft_strnstr.c	ft_isascii.c ft_memset.c ft_striteri.c ft_strrchr.c ft_isdigit.c ft_putchar_fd.c ft_strjoin.c ft_strtrim.c ft_isprint.c ft_putendl_fd.c ft_strlcat.c ft_substr.c ft_printf.c hfuncs.c hfuncs2.c ft_lstadd_back.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstsize.c ft_lstadd_front.c ft_lstdelone.c ft_lstlast.c ft_lstnew.c get_next_line.c get_next_line_utils.c

OBJS = ${SRCS:.c=.o}

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@ar rc ${NAME} ${OBJS}
	@ranlib ${NAME}

all: ${NAME}

clean:
	@rm -f ${OBJS}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
