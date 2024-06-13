/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/13 15:57:30 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*find_pipe(t_list *tokens)
{
	t_iterable	current;

	set_iterable(&current, tokens);
	while (current.node)
	{
		if (current.type == T_PIPE)
			return (current.node);
		set_iterable(&current, current.node->next);
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

void	build_tree_pipe(t_tree **tree, t_list *node, t_data *data)
{
	t_list	*tokens;
	t_tree	*left;
	t_tree	*right;

	tokens = (*tree)->content;
	data->tree = tree_new(NULL, data);
	if (data->tree == NULL)
		error_exit(MALLOC, data);
	data->tree->left = tree_new(NULL, data);
	data->tree->right = tree_new(NULL, data);
	left = data->tree->left;
	right = data->tree->right;
	if (left == NULL || right == NULL)
		error_exit(MALLOC, data);
	left->content = copy_tokens(tokens, list_node_index(tokens, node), data);
	data->tree->content = copy_tokens(node, 1, data);
	right->content = copy_tokens(node->next, list_size(node->next), data);
	if (left->content == NULL || right->content == NULL
		|| data->tree->content == NULL)
		error_exit(MALLOC, data);
	tree_clear(tree);
	*tree = data->tree;
}

void	build_tree_split(t_tree **tree, t_data *data)
{
	t_list	*tokens;
	t_tree	*left;

	tokens = (*tree)->content;
	if (list_size(tokens) == 1)
		return ;
	data->tree = tree_new(NULL, data);
	if (data->tree == NULL)
		error_exit(MALLOC, data);
	data->tree->left = tree_new(NULL, data);
	left = data->tree->left;
	if (left == NULL)
		error_exit(MALLOC, data);
	data->tree->content = copy_tokens(tokens, 1, data);
	left->content = copy_tokens(tokens->next, list_size(tokens->next), data);
	if (data->tree->content == NULL || left->content == NULL)
		error_exit(MALLOC, data);
	tree_clear(tree);
	*tree = data->tree;
	build_tree_split(&(*tree)->left, data);
}

/*
ls < f -a

->

<
	f
		ls
			-a
*/
// void	build_tree_broket(t_tree **tree, t_data *data)
// {

// }

void	build_tree(t_tree **tree, t_data *data)
{
	t_list	*node;

	if (*tree == NULL)
		return ;
	node = find_pipe((*tree)->content);
	if (node)
		build_tree_pipe(tree, node, data);
	else
	{
		node = find_brokets((*tree)->content);
		// if (node)
		// 	build_tree_broket(tree, node, data);
		// else
			build_tree_split(tree, data);
	}
	build_tree(&(*tree)->left, data);
	build_tree(&(*tree)->right, data);
}

int	main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	while (1)
	{
		data.input = readline("minishell> ");
		if (data.input == NULL)
			ft_putendl_fd("readline error", 2);
		else
		{
			if (ft_strcmp(data.input, "exit") == 0)
				return (free_all(&data), 0);
			if (data.input[0] != '\0' && !ft_strisspace(data.input))
				add_history(data.input);

			get_tokens(&data);
			if (lexing(&data))
				ft_putendl_fd("lexing error", 2);
			// list_print(data.tokens, print_token);

			init_ast(&data);
			build_tree(&data.ast, &data);
			tree_print(data.ast);

			free(data.input);
			list_clear(&data.tokens, free_token);
			tree_clear(&data.ast);
		}
	}
	return (free_all(&data), 0);
}
