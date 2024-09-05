SRC =   main.c \
		lexer.c \
		excecutor.c
		
OBJS = ${SRC:.c=.o}
NAME = minishell
CC = cc
CFLAGS = -Werror -Wextra -Wall
LIBFT_PATH = ./libft
RM = rm -f

# Define colors
DEF_COLOR = \033[0;39m
ORANGE = \033[0;33m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[1;92m
YELLOW = \033[1;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all: libft ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} -L${LIBFT_PATH} -lft -lreadline

libft:
	if [ ! -d "$(LIBFT_PATH)" ]; then \
        echo "downloading libft..."; \
		git clone git@github.com:Sergio0227/Libft.git $(LIBFT_PATH); \
	fi
	${MAKE} all -C ${LIBFT_PATH}

.c.o:
	${CC} -g -c $< -o ${<:.c=.o}


clean:
	${MAKE} -C ${LIBFT_PATH} clean 
	${RM} ${OBJS}


fclean: clean
	${RM} ${NAME};
	${RM} -rf ${LIBFT_PATH}

re: fclean all

.PHONY: all clean fclean re libft
