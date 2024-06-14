/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:44:54 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/14 19:45:06 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*find_pipe(t_list *tokens)
{
	t_iterable	current;

	set_iterable(&current, list_last(tokens));
	while (current.node)
	{
		if (current.type == T_PIPE)
			return (current.node);
		set_iterable(&current, current.node->previous);
	}
	return (NULL);
}

t_list	*find_brokets(t_list *tokens)
{
	t_iterable	current;

	set_iterable(&current, tokens);
	while (current.node)
	{
		if (current.type == T_BROKET_LEFT || current.type == T_BROKET_RIGHT
			|| current.type == T_DOUBLE_BROKET_LEFT
			|| current.type == T_DOUBLE_BROKET_RIGHT)
			return (current.node);
		set_iterable(&current, current.node->next);
	}
	return (NULL);
}

void	new_tree(t_data *data)
{
	data->tree = tree_new(NULL, data);
	data->tree->left = tree_new(NULL, data);
	data->tree->right = tree_new(NULL, data);
	if (data->tree == NULL || data->tree->left == NULL
		|| data->tree->right == NULL)
		error_exit(MALLOC, data);
}
