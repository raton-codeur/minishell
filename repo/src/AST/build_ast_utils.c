/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:44:54 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/13 17:06:34 by qhauuy           ###   ########.fr       */
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

static int	copy_token_content(t_iterable current, t_iterable *current_copy)
{
	current_copy->content = ft_strdup(current.content);
	if (!current_copy->content)
		return (1);
	current_copy->token = ft_calloc(1, sizeof(t_token));
	if (!current_copy->token)
		return (free(current_copy->content), 1);
	current_copy->token->content = current_copy->content;
	current_copy->token->type = current.type;
	current_copy->node = list_new(current_copy->token);
	if (!current_copy->node)
	{
		free(current_copy->content);
		free(current_copy->token);
		return (1);
	}
	return (0);
}

t_list	*copy_tokens(t_list *tokens, int size, t_data *data)
{
	int			i;
	t_list		*result;
	t_iterable	current;
	t_iterable	current_copy;

	if (size == 0 || !tokens)
		return (NULL);
	i = 0;
	result = NULL;
	set_iterable(&current, tokens);
	while (i < size && current.node)
	{
		if (copy_token_content(current, &current_copy))
		{
			list_clear(&result, free_token);
			error_exit(MALLOC, data);
		}
		list_add_back(&result, current_copy.node);
		set_iterable(&current, current.node->next);
		i++;
	}
	return (result);
}
