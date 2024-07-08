/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:48:14 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/08 13:03:12 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_kv	*new_kv(char *env_line)
{
	t_kv	*result;
	int		i;

	result = ft_calloc(1, sizeof(t_kv));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (env_line[i] && env_line[i] != '=')
		i++;
	result->key = ft_substr(env_line, 0, i);
	if (env_line[i] != '=')
		return (free_kv(result), NULL);
	else
		result->value = ft_substr(env_line, i + 1, ft_strlen(env_line) - i - 1);
	if (result->key == NULL || result->value == NULL)
		return (free_kv(result), NULL);
	return (result);
}

void	add_to_env(char *env_line, t_data *data)
{
	t_kv	*new_content;
	t_list	*new_node;

	new_content = new_kv(env_line);
	if (new_content == NULL)
		return (error_exit(MALLOC, data));
	new_node = list_new(new_content);
	if (new_node == NULL)
		return (free_kv(new_content), error_exit(MALLOC, data));
	list_add_back(&data->env, new_node);
}

void	remove_from_env(char *key, t_data *data)
{
	t_list	*node;

	node = in_env(key, data);
	if (node == NULL)
		return ;
	list_remove_node(&data->env, node, free_kv);
}
