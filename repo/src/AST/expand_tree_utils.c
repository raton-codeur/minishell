/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:44:54 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/13 16:23:04 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_list	*find_pipe(t_list **node, t_tree *tree)
{
	t_iterable	current;

	set_iterable(&current, list_last(tree->content));
	while (current.node)
	{
		if (current.type == T_PIPE)
		{
			*node = current.node;
			return (*node);
		}
		set_iterable(&current, current.node->previous);
	}
	*node = NULL;
	return (NULL);
}

t_list	*find_broket(t_list **node, t_tree *tree)
{
	t_iterable	current;

	set_iterable(&current, tree->content);
	while (current.node)
	{
		if (current.type == T_BROKET_LEFT
			|| current.type == T_BROKET_RIGHT
			|| current.type == T_DOUBLE_BROKET_LEFT
			|| current.type == T_DOUBLE_BROKET_RIGHT)
		{
			*node = current.node;
			return (*node);
		}
		set_iterable(&current, current.node->next);
	}
	*node = NULL;
	return (NULL);
}

t_tree	*new_tree(t_list *tokens, t_data *data)
{
	data->tree = ft_calloc(1, sizeof(t_tree));
	if (data->tree == NULL)
		error_exit(MALLOC, data);
	data->tree->left = ft_calloc(1, sizeof(t_tree));
	data->tree->right = ft_calloc(1, sizeof(t_tree));
	if (data->tree->left == NULL || data->tree->right == NULL)
		error_exit(MALLOC, data);
}
