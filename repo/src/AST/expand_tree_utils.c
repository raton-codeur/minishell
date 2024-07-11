/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:44:54 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/11 23:57:54 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"

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
		if (current.type == T_BROKET_LEFT
			|| current.type == T_BROKET_RIGHT
			|| current.type == T_DOUBLE_BROKET_LEFT
			|| current.type == T_DOUBLE_BROKET_RIGHT)
			return (current.node);
		set_iterable(&current, current.node->next);
	}
	return (NULL);
}

static t_tree	*get_new_tree(t_list *tokens, t_data *data)
{
	t_tree	*result;

	result = ft_calloc(1, sizeof(t_tree));
	if (result == NULL)
		error_exit(MALLOC, data);
	result->content = tokens;
	return (result);
}

void	set_new_tree(t_data *data)
{
	data->tree = get_new_tree(NULL, data);
	if (data->tree == NULL)
		error_exit(MALLOC, data);
	data->tree->left = get_new_tree(NULL, data);
	data->tree->right = get_new_tree(NULL, data);
	if (data->tree->left == NULL || data->tree->right == NULL)
		error_exit(MALLOC, data);
}
