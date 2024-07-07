/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:41:50 by jteste            #+#    #+#             */
/*   Updated: 2024/07/07 18:33:38 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"



char	*get_key(t_list *node)
{
	return (((t_kv *)node->content)->key);
}

char	*get_value(t_list *node)
{
	return (((t_kv *)node->content)->value);
}

char	*get_from_env(char *key, t_data *data)
{
	t_list	*current;

	current = data->env;
	while (current)
	{
		if (!ft_strncmp(get_key(current), key, ft_strlen(get_key(current))))
			return (get_value(current));
		current = current->next;
	}
	return (NULL);
}


// char	**env_double_array(t_list *envp, t_data *data)
// {
// 	char	**env;
// 	char	*tmp;
// 	t_list	*current;
// 	int		i;

// 	i = 0;
// 	current = envp;
// 	env = ft_calloc(list_size(envp) + 1, sizeof(char *));
// 	if (env == NULL)
// 		error_exit(MALLOC, data);
// 	env[list_size(envp)] = NULL;
// 	while (current)
// 	{
// 		tmp = ft_strjoin(((t_envp *)current->content)->key, "=");
// 		env[i] = ft_strjoin(tmp, ((t_envp *)current->content)->value);
// 		free(tmp);
// 		current = current->next;
// 		i++;
// 	}
// 	return (env);
// }

// void	env_(t_data *data, t_list **envp, int in_parent)
// {
// 	t_list	*current;
// 	char	*buff;
// 	char	*join;

// 	current = *envp;
// 	while (current)
// 	{
// 		if (((t_envp *)current->content)->value == NULL
// 			|| ft_strcmp(((t_envp *)current->content)->value, "") == 0)
// 		{
// 			current = current->next;
// 			continue ;
// 		}
// 		buff = ft_strjoin(((t_envp *)current->content)->key, "=");
// 		if (buff == NULL)
// 			return (error_exit(MALLOC, NULL));
// 		join = ft_strjoin(buff, ((t_envp *)current->content)->value);
// 		if (join == NULL)
// 			return (error_exit(MALLOC, NULL));
// 		free(buff);
// 		printf("%s\n", join);
// 		free(join);
// 		current = current->next;
// 	}
// 	if (!in_parent)
// 		return (free_all(data), exit(0));
// }
