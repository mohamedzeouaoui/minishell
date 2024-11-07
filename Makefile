CC = cc
CFLAGS = -Werror -Wextra -Wall -g3 #-fsanitize=address
RM = rm -rf
GARBAGE = ./garbage_collector/ft_memory_management.c
UTILS = ./utils/ft_cmd_join.c ./utils/ft_lst.c ./utils/ft_strdup.c
PARSING = ./parsing/lexer.c
CFILES = main.c  ${PARSING} ${UTILS} ${GARBAGE}
OFILES = ${CFILES:.c=.o}
NAME = minishell

all : ${NAME}

${NAME} : ${OFILES}
	${CC} ${OFILES} -lreadline -o ${NAME}

%.o: %.c
	${CC} -c $< -o $@

clean :
	${RM} ${OFILES}

fclean : clean
	${RM} ${NAME}

re : fclean all
