/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:44:54 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/13 23:05:56 by qhauuy           ###   ########.fr       */
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
		if (get_broket(current.node))
		{
			*node = current.node;
			return (*node);
		}
		set_iterable(&current, current.node->next);
	}
	*node = NULL;
	return (NULL);
}

void	new_tree(t_data *data)
{
	data->tree = ft_calloc(1, sizeof(t_tree));
	if (data->tree == NULL)
		error_exit(MALLOC, data);
	data->tree->left = ft_calloc(1, sizeof(t_tree));
	data->tree->right = ft_calloc(1, sizeof(t_tree));
	if (data->tree->left == NULL || data->tree->right == NULL)
		error_exit(MALLOC, data);
}

static t_list	*get_copy(t_list *node)
{
	t_token		*token;
	t_iterable	new;

	token = node->content;
	new.content = ft_strdup(token->content);
	if (new.content == NULL)
		return (NULL);
	new.token = ft_calloc(1, sizeof(t_token));
	if (new.token == NULL)
		return (free(new.content), NULL);
	new.token->content = new.content;
	new.token->type = token->type;
	new.node = list_new(new.token);
	if (new.node == NULL)
		return (free_token(new.token), NULL);
	return (new.node);
}

t_list	*get_tokens(t_list *tokens, int size, t_data *data)
{
	t_list		*result;
	int			i;
	t_list		*current;
	t_list		*current_copy;

	if (size == 0 || tokens == NULL)
		return (NULL);
	i = 0;
	result = NULL;
	current = tokens;
	while (i < size && current)
	{
		current_copy = get_copy(current);
		if (current_copy == NULL)
		{
			list_clear(&result, free_token);
			error_exit(MALLOC, data);
		}
		list_add_back(&result, current_copy);
		current = current->next;
		i++;
	}
	return (result);
}
