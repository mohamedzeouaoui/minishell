CC = cc
#CFLAGS = -Werror -Wextra -Wall -g3 #-fsanitize=address
RM = rm -rf
UTILS = ./utils/garbage_collector/ft_memory_management.c ./utils/ft_cmd_join.c ./utils/ft_iswhitespace.c \
	./utils/ft_lstsize.c ./utils/ft_lst.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlen.c \
	./utils/ft_strncmp.c ./utils/ft_substr.c  ./utils/ft_print.c ./utils/print_errore.c ./utils/ft_putstr_fd.c \
	./utils/ft_split.c ./utils/ft_itoa.c
ENV = ./env/env.c ./env/env_utils.c ./env/ft_parse_env.c ./env/env_export.c 
PARSING = ./parsing/lexer.c ./parsing/parse_redirections.c ./parsing/syntax_error.c ./parsing/expand/expand.c \
			./parsing/expand/expand_helper.c 
EXECUTION = ./execution/execution.c ./execution/builtins/builtins.c ./execution/builtins/ft_echo.c \
	./execution/builtins/ft_cd.c ./execution/exit_file.c ./execution/builtins/ft_pwd.c \
	./execution/builtins/ft_env.c ./execution/builtins/ft_unset.c ./execution/builtins/ft_exit.c \
	./execution/file_redirection.c ./execution/pipe_fork_dup.c ./execution/utils_exec.c ./execution/builtins/ft_export.c 
CFILES = test.c  ${PARSING} ${UTILS} ${EXECUTION} ${ENV}
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