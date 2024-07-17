/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:48:14 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/17 16:43:02 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_proper(char *envp_line)
{
	if (ft_strchr(envp_line, '=') == NULL)
		return (ft_strisword(envp_line));
	else
	{
		if (!ft_isword_start(*envp_line))
			return (0);
		envp_line++;
		while (*envp_line != '=')
		{
			if (!ft_isword_content(*envp_line))
				return (0);
			envp_line++;
		}
		return (1);
	}
}

static t_kv	*get_kv(char *envp_line)
{
	t_kv	*result;
	int		i;

	result = ft_calloc(1, sizeof(t_kv));
	if (result == NULL)
		return (NULL);
	if (!is_proper(envp_line) || (ft_strchr(envp_line, '=') == NULL))
	{
		result->key = ft_strdup(envp_line);
		if (result->key == NULL)
			return (free_kv(result), NULL);
	}
	else
	{
		i = 0;
		while (envp_line[i] != '=')
			i++;
		result->key = ft_substr(envp_line, 0, i++);
		result->value = ft_substr(envp_line, i, ft_strlen(envp_line) - i);
		if (result->key == NULL || result->value == NULL)
			return (free_kv(result), NULL);
	}
	return (result);
}

t_list	*insert_in_env(char *envp_line, t_data *data)
{
	t_kv	*kv;
	t_list	*result;

	kv = get_kv(envp_line);
	if (kv == NULL)
		return (error_exit(MALLOC, data), NULL);
	if (in_env(kv->key, data))
	{
		result = in_env(kv->key, data);
		reset_value(kv->key, kv->value, data);
		free(kv->key);
		free(kv);
	}
	else
	{
		result = list_new(kv);
		if (result == NULL)
			return (free_kv(kv), error_exit(MALLOC, data), NULL);
		list_add_back(&data->env, result);
	}
	return (result);
}

static char	*get_envp_line(t_list *node)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(get_key(node), "=");
	if (tmp == NULL)
		return (NULL);
	result = ft_strjoin(tmp, get_value(node));
	free(tmp);
	return (result);
}

char	**get_envp(t_data *data)
{
	char	**result;
	t_list	*current;
	int		i;

	current = data->env;
	result = ft_calloc(list_size(data->env) + 1, sizeof(char *));
	if (result == NULL)
		error_exit(MALLOC, data);
	i = 0;
	while (current)
	{
		if (get_value(current))
		{
			result[i] = get_envp_line(current);
			if (result[i] == NULL)
			{
				deep_free((void **)result, i);
				return (error_exit(MALLOC, data), NULL);
			}
			i++;
		}
		current = current->next;
	}
	result[i] = NULL;
	return (result);
}
