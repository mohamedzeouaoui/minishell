/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:02:54 by asodor            #+#    #+#             */
/*   Updated: 2025/01/09 02:00:01 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

#include <assert.h>

# define p_inp 1
# define p_outp 0

typedef struct s_files t_files;

typedef struct s_data
{
	char **args;         //--> cmd args ex: "ls" "-la"
	t_files *files;      //
	struct s_data *next; // next node
}					t_data;

typedef struct s_stack
{
	void			*ptr;
	struct s_stack	*next;
}					t_stack;

typedef struct s_files
{
	char			*redirection; 
	char			*file;
	int heredoc_fd;
	struct s_files	*next;
}					t_files;

typedef struct s_env {
	char *key;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_shell
{
	t_env	*env;
	int		exit_status;
	char	*pwd;
	int		herdoc;
} t_shell;

typedef struct s_helper
{
	int i;
	int j;
	int quote;
	char *result;
	bool from_env;
} t_helper;

// utils
unsigned int	ft_strlen(const char *s1);
char    *ft_strdup(const char *s1);
char    *ft_strdup_normal(const char *s1);
char    *ft_strjoin(char const *s1, char const *s2, size_t n);
int	ft_iswhitespace(int c);
void    *mallocc(size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_data  *ft_lstnew(void);
char    **ft_cmd_join(char **original_arr, char *new_str);
void	ft_lstadd_back(t_data **lst, t_data *new);
int	ft_print_err(char *err);
void	ft_print_err1(char *s1, char *s2, char *s3, int f);
int	ft_lstsize(t_data *lst);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
int print_errore(char *error);
int print_errore_mix(char *error, char *error2, char *error3, int exit_status);
int print_errore_exit(char *error, int exit_status);
char	**ft_split(char const *s, char c);
char *ft_itoa(int n);
int	ft_lstsize_env(t_env *lst);
int ft_isalpha(char c);
int ft_isalnum(int c);
char *ft_strcpy(char *str, char *str2);
char *ft_strcat(char *str, char *str2);
char	*ft_strchr(const char *s, int c);

//----> set_last_arg

// parsing
t_data *tokenize_input(char *input);
void parse_redirections(t_data *cmd_list);
t_data	*ft_errors(t_data *cmd_list);
t_shell *get_shell_state(void);
// expand
void ft_dollar_sign(t_helper *h, char *str);
void ft_handle_quotes(t_helper *h, char *str);
void ft_get_var_value(t_helper *h, char *str);
char **ft_remove_quotes(char *file);
void ft_expand(t_data *cmd_list);

// heredoc
int	ft_isdigit(int d);
int	ft_isalnum(int c);
char *expand_env_var(char *str);
char *ft_get_name(int *i, char *str);
int ft_heredoc(t_data *cmd_list);

// env
t_env *ft_env_new_node(char *k, char *v);
char *ft_key(char *env, int *i) ;
char *ft_value(char *env, int *i);
void	ft_parse_env(char **env, t_shell *shell);
t_env *search_in_env(char *key);
char **env_lst_to_tab(void);
char **export_env_sorted(void);
void ft_add_env(t_env **env, t_env *new);


// execution
void    ft_exec(t_data *data, int size);
int check_built(t_data *data, int prosses);
char **env_lst_to_tab(void);
void ft_builtins_run(t_data *data, int prosses);
int is_builtins(t_data *data);
void    exit_clean(int exit_status);
void files_pipe(int fd_pipe[2], int fd_stdout_stored, int size, int i);
int command_execution(t_data *data, int size);
void check_in_env_path_cmd(char *cmd, t_data *data);
bool check_slash_in_path(char *path);
int check_dirctory(char *path);
void command_not_found(t_data *data);
void check_run_path_not_commande(char *path, t_data *data);

//SIGNALS

void	signal_cases_handel(int cas);



// builtins
int ft_echo(t_data *data);
int ft_cd(t_data *data);
int ft_env(char **env, int prosses);
int ft_pwd(void);
void pwd_intialize(void);
void ft_exit(t_data *data, int prosses, int *exit_status);
int ft_unset(t_data *data);
void    ft_export(t_data *data, int *exit_status);

//redirection
int ft_dup2(int fd1, int fd2);
int input_file_clear(t_files *file);
int input_file_append(t_files *file);
int file_redirection(t_files *file, int prosses);


#endif