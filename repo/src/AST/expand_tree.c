/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:44:09 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/12 00:22:53 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"

static int	expand_tree_pipe(t_tree **tree, t_list *node, t_data *data)
{
	t_list	*tokens;
	t_tree	*left;
	t_tree	*right;

	tokens = (*tree)->content;
	set_new_tree(data);
	left = data->tree->left;
	right = data->tree->right;
	if (list_node_index(tokens, node) == 0)
		return (syntax_error("|", data), 1);
	left->content = copy_tokens(tokens, list_node_index(tokens, node), data);
	data->tree->content = copy_tokens(node, 1, data);
	if (list_size(node->next) == 0)
		return (syntax_error("|", data), 1);
	right->content = copy_tokens(node->next, list_size(node->next), data);
	if (data->tree->content == NULL
		|| left->content == NULL || right->content == NULL)
		error_exit(MALLOC, data);
	tree_clear(tree);
	*tree = data->tree;
	data->tree = NULL;
	return (0);
}

static void	expand_tree_broket(t_tree **tree, t_list *node, t_data *data)
{
	t_iterable	current;
	t_iterable	next;

	set_iterables(&current, &next, node);
	set_new_tree(data);
	data->tree->content = copy_tokens(node, 1, data);
	data->tree->left->content = copy_tokens(node->next, 1, data);
	list_remove_node((t_list **)&(*tree)->content, node->next, free_token);
	list_remove_node((t_list **)&(*tree)->content, node, free_token);
	data->tree->right->content = \
		copy_tokens((*tree)->content, list_size((*tree)->content), data);
	if ((*tree)->content == NULL)
		tree_clear(&data->tree->right);
	if (data->tree->content == NULL || data->tree->left->content == NULL
		|| (data->tree->right && data->tree->right->content == NULL))
		error_exit(MALLOC, data);
	tree_clear(tree);
	*tree = data->tree;
	data->tree = NULL;
}

static void	expand_tree_split(t_tree **tree, t_data *data)
{
	t_tree	*left;
	t_list	*node;

	if (!(*tree)->content || list_size((*tree)->content) == 1)
		return ;
	data->tree = tree_new(NULL, data);
	if (data->tree == NULL)
		error_exit(MALLOC, data);
	data->tree->left = tree_new(NULL, data);
	left = data->tree->left;
	if (left == NULL)
		error_exit(MALLOC, data);
	data->tree->content = copy_tokens((*tree)->content, 1, data);
	node = (*tree)->content;
	left->content = copy_tokens(node->next, list_size(node->next), data);
	if (data->tree->content == NULL || left->content == NULL)
		error_exit(MALLOC, data);
	tree_clear(tree);
	*tree = data->tree;
	data->tree = NULL;
	expand_tree_split(&(*tree)->left, data);
}

// void	expand_tree(t_tree **tree, t_data *data)
// {
// 	t_list	*node;

// 	if (*tree == NULL)
// 		return ;
// 	node = find_pipe((*tree)->content);
// 	if (node)
// 	{
// 		if (expand_tree_pipe(tree, node, data))
// 			return ;
// 	}
// 	else
// 	{
// 		node = find_brokets((*tree)->content);
// 		if (node)
// 			expand_tree_broket(tree, node, data);
// 		expand_tree_split(tree, data);
// 	}
// 	expand_tree(&(*tree)->left, data);
// 	if (*tree != NULL)
// 		expand_tree(&(*tree)->right, data);
// }
