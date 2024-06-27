/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:41:50 by jteste            #+#    #+#             */
/*   Updated: 2024/06/27 13:09:15 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_envp	*copy_env_line(char *env_line)
{
	t_envp	*new_content;
	char	**split_line;

	new_content = ft_calloc(1, sizeof(t_envp));
	if (new_content == NULL)
		return (NULL);
	split_line = ft_split_once(env_line, '=');
	if (split_line == NULL)
		return (NULL);
	new_content->key = ft_strdup(split_line[0]);
	if (new_content->key == NULL)
		return (NULL);
	new_content->value = ft_strdup(split_line[1]);
	if (new_content->value == NULL)
		return (NULL);
	deep_free((void **)split_line, 2);
	return (new_content);
}

int	copy_env(t_data *data, char **envp)
{
	int		i;
	t_envp	*new_content;
	t_list	*new_node;

	i = 0;
	if (envp == NULL || envp[0] == NULL || envp[0][0] == '\0')
		return (1);
	while (envp[i])
	{
		new_content = copy_env_line(envp[i]);
		if (new_content == NULL)
			return (error_exit(MALLOC, data), 1);
		new_node = list_new(new_content);
		if (new_node == NULL)
			return (error_exit(MALLOC, data), 1);
		list_add_back(&data->envp, new_node);
		i++;
	}
	return (0);
}

char	*get_env(char *key, t_list *envp)
{
	t_list	*current;

	current = envp;
	while (current)
	{
		if (ft_strcmp(((t_envp *)current->content)->key, key) == 0)
			return (((t_envp *)current->content)->value);
		current = current->next;
	}
	return (NULL);
}

void	print_env(t_list **envp)
{
	t_list	*current;
	char	*buff;
	char	*join;

	current = *envp;
	while (current)
	{
		buff = ft_strjoin(((t_envp *)current->content)->key, "=");
		join = ft_strjoin(buff, ((t_envp *)current->content)->value);
		free(buff);
		buff = ft_strjoin(join, "\n");
		free(join);
		printf("%s", buff);
		free(buff);
		current = current->next;
	}
}

char	**env_double_array(t_list *envp, t_data *data)
{
	char	**env;
	char	*tmp;
	t_list	*current;
	int		i;
	
	i = 0;
	current = envp;
	env = ft_calloc(list_size(envp) + 1, sizeof(char *));
	if (env == NULL)
		error_exit(MALLOC, data);
	env[list_size(envp)] = NULL;
	while (current)
	{
		tmp = ft_strjoin(((t_envp *)current->content)->key, "=");
		env[i] = ft_strjoin(tmp, ((t_envp *)current->content)->value);
		free(tmp);
		current = current->next;
		i++;
	}
	return (env);
}


