/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:48:14 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/17 16:01:17 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_value(char *envp_line)
{
	int	i;

	if (ft_strchr(envp_line, '=') == NULL)
		return (0);
	if (envp_line[0] == '=')
		return (0);
	i = 0;
	while (envp_line[i] != '=')
		i++;
	i++;
	if (envp_line[i] == '\0')
		return (0);
	if (envp_line[i] == '\0' && envp_line[i - 1] == '=')
		return (0);
	return (1);
}

static t_kv	*get_kv(char *envp_line)
{
	t_kv	*result;
	int		i;

	result = ft_calloc(1, sizeof(t_kv));
	if (result == NULL)
		return (NULL);
	i = 0;
	if (!has_value(envp_line))
	{
		if (envp_line[ft_strlen(envp_line) - 1] == '=')
		{
			envp_line[ft_strlen(envp_line) - 1] = '\0';
			result->key = ft_strdup(envp_line);
			result->value = ft_strdup("");
			if (result->value == NULL)
				return (free_kv(result), NULL);
		}
		else
		{
			result->key = ft_strdup(envp_line);
			result->value = NULL;
		}
	}
	else
	{
		while (envp_line[i] != '='
			&& envp_line[i] != '+' && envp_line[i] != '-')
			i++;
		result->key = ft_substr(envp_line, 0, i++);
		result->value = ft_substr(envp_line, i, ft_strlen(envp_line) - i);
		if (result->value == NULL)
			return (free_kv(result), NULL);
	}
	if (result->key == NULL)
		return (free_kv(result), NULL);
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
		if (get_value(current) && get_value(current)[0] != '\0')
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
