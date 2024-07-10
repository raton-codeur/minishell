/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:41:50 by jteste            #+#    #+#             */
/*   Updated: 2024/07/10 12:42:40 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*get_key(t_list *node)
{
	if (node == NULL)
		return (NULL);
	return (((t_kv *)node->content)->key);
}

char	*get_value(t_list *node)
{
	if (node == NULL)
		return (NULL);
	return (((t_kv *)node->content)->value);
}

t_list	*in_env(char *key, t_data *data)
{
	t_list	*current;

	current = data->env;
	while (current)
	{
		if (ft_strcmp(get_key(current), key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	reset_value(char *key, char *new_value, t_data *data)
{
	t_list	*node;
	t_kv	*kv;

	node = in_env(key, data);
	if (node == NULL)
		return ;
	kv = node->content;
	free(kv->value);
	kv->value = new_value;
}

void	remove_from_env(char *key, t_data *data)
{
	t_list	*node;

	node = in_env(key, data);
	if (node == NULL)
		return ;
	list_remove_node(&data->env, node, free_kv);
}
