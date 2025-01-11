/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:18:48 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/01/11 01:15:52 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_env_alphabetically(char **env, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**export_env_sorted(void)
{
	t_env	*tmp;
	char	**env;
	int		i;

	i = 0;
	tmp = get_shell_state()->env;
	env = (char **)mallocc(sizeof(char *) * (ft_lstsize_env(tmp) + 1));
	if (!env)
		return (NULL);
	while (tmp)
	{
		env[i] = ft_strjoin(tmp->key, "=", 0);
		env[i] = ft_strjoin(env[i], tmp->value, 0);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	sort_env_alphabetically(env, ft_lstsize_env(get_shell_state()->env));
	return (env);
}

int	allocate_variable(char *variable, char **var)
{
	int	i;
	int	count;

	i = 0;
	while (variable[i] && variable[i] != '=' && variable[i] != '+')
		i++;
	(*var) = (char *)mallocc(sizeof(char) * (i + 1));
	count = i;
	i = -1;
	while (++i < count)
		(*var)[i] = variable[i];
	(*var)[i] = '\0';
	return (count);
}

void	append_env(char *var, char *value)
{
	t_env	*tmp;
	char	*new_value;

	tmp = search_in_env(var);
	new_value = (char *)mallocc(sizeof(char) * (ft_strlen(tmp->value)
				+ ft_strlen(value) + 1));
	new_value = ft_strcpy(new_value, tmp->value);
	new_value = ft_strcat(new_value, value);
	free(tmp->value);
	tmp->value = new_value;
}
