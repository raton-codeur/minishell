/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:19:45 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/13 22:57:14 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	split_tree_pipe(t_tree **tree, t_list *pipe, t_data *data)
{
	t_list	*tokens;

	tokens = (*tree)->content;
	if (list_node_index(tokens, pipe) == 0)
		return (syntax_error("|", data));
	new_tree(data);
	data->tree->left->content
		= get_tokens(tokens, list_node_index(tokens, pipe), data);
	data->tree->content = get_tokens(pipe, 1, data);
	if (list_size(pipe->next) == 0)
		return (syntax_error("|", data));
	data->tree->right->content
		= get_tokens(pipe->next, list_size(pipe->next), data);
	if (data->tree->content == NULL
		|| data->tree->left->content == NULL
		|| data->tree->right->content == NULL)
		error_exit(MALLOC, data);
	tree_clear(tree);
	*tree = data->tree;
	data->tree = NULL;
	expand_tree(&(*tree)->left, data);
	if (*tree)
		expand_tree(&(*tree)->right, data);
}

static void	split_tree_broket(t_tree **tree, t_list *broket, t_data *data)
{
	new_tree(data);
	data->tree->content = get_tokens(broket, 1, data);
	data->tree->left->content = get_tokens(broket->next, 1, data);
	list_remove_node((t_list **)&(*tree)->content, broket->next, free_token);
	list_remove_node((t_list **)&(*tree)->content, broket, free_token);
	data->tree->right->content
		= get_tokens((*tree)->content, list_size((*tree)->content), data);
	if ((*tree)->content == NULL)
		tree_clear(&data->tree->right);
	if (data->tree->content == NULL
		|| data->tree->left->content == NULL
		|| (data->tree->right && data->tree->right->content == NULL))
		error_exit(MALLOC, data);
	tree_clear(tree);
	*tree = data->tree;
	data->tree = NULL;
	expand_tree(&(*tree)->right, data);
}

static void	split_tree(t_tree **tree, t_data *data)
{
	t_list	*tokens;

	tokens = (*tree)->content;
	if (tokens == NULL || list_size(tokens) == 1)
		return ;
	new_tree(data);
	tree_clear(&data->tree->left);
	data->tree->content = get_tokens(tokens, 1, data);
	data->tree->right->content
		= get_tokens(tokens->next, list_size(tokens->next), data);
	if (data->tree->content == NULL || data->tree->right->content == NULL)
		error_exit(MALLOC, data);
	tree_clear(tree);
	*tree = data->tree;
	data->tree = NULL;
	split_tree(&(*tree)->right, data);
}

void	expand_tree(t_tree **tree, t_data *data)
{
	t_list	*node;

	if (*tree == NULL)
		return ;
	if (find_pipe(&node, *tree))
		split_tree_pipe(tree, node, data);
	else if (find_broket(&node, *tree))
		split_tree_broket(tree, node, data);
	else
		split_tree(tree, data);
}

void	build_ast(t_data *data)
{
	if (data->tokens == NULL)
		return ;
	data->ast = ft_calloc(1, sizeof(t_tree));
	if (data->ast == NULL)
		error_exit(MALLOC, data);
	data->ast->content = get_tokens(\
		data->tokens, list_size(data->tokens), data);
	expand_tree(&data->ast, data);
}
