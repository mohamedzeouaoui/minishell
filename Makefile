CC = cc
CFLAGS = -Werror -Wextra -Wall -g3 #-fsanitize=address
RM = rm -rf
UTILS = ./utils/garbage_collector/ft_memory_management.c ./utils/ft_cmd_join.c ./utils/ft_iswhitespace.c ./utils/ft_lst.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_substr.c  
PARSING = ./parsing/lexer.c ./parsing/parse_redirections.c ./parsing/syntax_error.c
CFILES = main.c  ${PARSING} ${UTILS}
OFILES = ${CFILES:.c=.o}
NAME = minishell

all : ${NAME}

${NAME} : ${OFILES}
	${CC} ${CFLAGS} ${OFILES} -lreadline -o ${NAME}

%.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

clean :
	${RM} ${OFILES}

fclean : clean
	${RM} ${NAME}

re : fclean all