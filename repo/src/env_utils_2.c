/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:48:14 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/08 17:58:16 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_good_line(char *env_line)
{
	int	i;

	if (ft_strchr(env_line, '=') == NULL)
		return (0);
	if (env_line[0] == '=')
		return (0);
	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	if (env_line[i] == '\0')
		return (0);
	return (1);
}

static t_kv	*new_kv(char *env_line)
{
	t_kv	*result;
	int		i;

	result = ft_calloc(1, sizeof(t_kv));
	if (result == NULL)
		return (NULL);
	i = 0;
	if (!is_good_line(env_line))
	{
		result->key = ft_strdup(env_line);
		result->value = ft_strdup("");
	}
	else
	{
		while (env_line[i] && env_line[i] != '=')
			i++;
		result->key = ft_substr(env_line, 0, i++);
		result->value = ft_substr(env_line, i, ft_strlen(env_line) - i);
	}
	if (result->key == NULL || result->value == NULL)
		return (free_kv(result), NULL);
	return (result);
}

t_list	*add_to_env(char *env_line, t_data *data)
{
	t_kv	*new_content;
	t_list	*new_node;
	t_list	*result;

	new_content = new_kv(env_line);
	if (new_content == NULL)
		return (error_exit(MALLOC, data), NULL);
	if (in_env(new_content->key, data))
	{
		result = in_env(new_content->key, data);
		reset_value(new_content->key, new_content->value, data);
		free(new_content->key);
		free(new_content);
		return (result);
	}
	else
	{
		new_node = list_new(new_content);
		if (new_node == NULL)
			return (free_kv(new_content), error_exit(MALLOC, data), NULL);
		list_add_back(&data->env, new_node);
		return (new_node);
	}
}

void	remove_from_env(char *key, t_data *data)
{
	t_list	*node;

	node = in_env(key, data);
	if (node == NULL)
		return ;
	list_remove_node(&data->env, node, free_kv);
}
