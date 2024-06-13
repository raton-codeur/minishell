/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/13 14:06:55 by qhauuy           ###   ########.fr       */
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

void	build_tree_pipe(t_data *data, t_tree **tree, t_list *node)
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
	if (data->tree->left == NULL || data->tree->right == NULL)
		error_exit(MALLOC, data);
	left->content = copy_tokens(tokens, node_position(tokens, node), data);
	data->tree->content = copy_tokens(node, 1, data);
	right->content = copy_tokens(node->next, list_size(node->next), data);
	if (left->content == NULL || right->content == NULL
		|| data->tree->content == NULL)
		error_exit(MALLOC, data);
	tree_clear(*tree);
	*tree = data->tree;
}

// t_list	*find_brokets(t_list *tokens)
// {
// 	t_iterable	current;

// 	set_iterable(&current, tokens);
// 	while (current.node)
// 	{
// 		if (current.type == T_BROKET_LEFT || current.type == T_BROKET_RIGHT
// 			|| current.type == T_DOUBLE_BROKET_LEFT
// 			|| current.type == T_DOUBLE_BROKET_RIGHT)
// 			return (current.node);
// 		set_iterable(&current, current.node->next);
// 	}
// 	return (NULL);
// }

// void	build_tree_broket(t_data *data, t_tree **tree, t_list *node, int position)
// {
// 	t_tree	*t_new;
// 	t_tree	*t_left;
// 	t_tree	*t_right;
// 	t_list	*l_new;
// 	t_list	*l_left;
// 	t_list	*l_right;

// 	l_left = copy_tokens(data, (*tree)->content, position);
// 	l_new = copy_tokens(data, node, 1);
// 	l_right = copy_tokens(data, node->next, list_size(node->next));

// 	t_new = tree_new(l_new, data);
// 	t_left = tree_new(l_left, data);
// 	t_right = tree_new(l_right, data);

// 	t_new->left = t_left;
// 	t_new->right = t_right;

// 	tree_clear(*tree);
// 	*tree = t_new;

// 	build_tree(data, &t_new->left);
// 	build_tree(data, &t_new->right);
// }

/*
echo bonjour toi

->

echo
	bonjour
		toi
*/
// void	split_tree(t_data *data, t_tree **tree)
// {
// 	t_list			*tokens;
// 	t_tree			*t_new;
// 	t_new_tokens	new_tokens;
	
// 	tokens = (*tree)->content;
// 	while (list_size((*tree)->content) > 1)
// 	{
// 		new_tokens.root = copy_tokens(data, tokens, 1);
// 		new_tokens.left = copy_tokens(data, tokens->next, list_size(tokens->next));
// 		t_new->content = tree_new(new_tokens.root, data);
// 		t_new->left = tree_new(new_tokens.left, data);
// 		t_new->right = NULL;
// 		*tree = t_new;

// 		split_tree(data, t_neww->left);
// 	}
// }

void	build_tree(t_data *data, t_tree **tree)
{
	t_list	*node;

	if (*tree == NULL)
		return ;
	node = find_pipe((*tree)->content);
	if (node)
		build_tree_pipe(data, tree, node);
	// else
	// {
	// 	node = find_brokets((*tree)->content);
	// 	if (node)
	// 		build_tree_broket(data, tree, node);
	// 	else
	// 		split_tree(data, tree);
	// }
	build_tree(data, &(*tree)->left);
	build_tree(data, &(*tree)->right);
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
				break ;
			if (data.input[0] != '\0' && !ft_strisspace(data.input))
				add_history(data.input);

			get_tokens(&data);
			if (lexing(&data))
				ft_putendl_fd("lexing error", 2);
			// list_print(data.tokens, print_token);

			init_ast(&data);
			build_tree(&data, &data.ast);
			tree_print(data.ast);

			free(data.input);
			list_clear(&data.tokens, free_token);
			tree_clear(data.ast);
		}
	}
	return (free_all(&data), 0);
}
