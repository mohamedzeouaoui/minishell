/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:02:54 by asodor            #+#    #+#             */
/*   Updated: 2024/11/19 19:23:52 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>

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
	//int heredoc_fd; //<-------
	struct s_files	*next;
}					t_files;

// utils
unsigned int	ft_strlen(const char *s1);
char    *ft_strdup(const char *s1);
char    *ft_strjoin(char const *s1, char const *s2, size_t n);
int	ft_iswhitespace(int c);
void    *mallocc(size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_data  *ft_lstnew(void);
char    **ft_cmd_join(char **original_arr, char *new_str);
void	ft_lstadd_back(t_data **lst, t_data *new);
//----> print_err
//----> ft_errors
//----> set_last_arg

// parsing
t_data *tokenize_input(char *input);
void parse_redirections(t_data *cmd_list);
int ft_errors(t_data *cmd_list);

#endif