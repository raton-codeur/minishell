/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/12 17:47:19 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*copy_tokens(t_data	*data)
{
	t_list		*result;
	t_iterable	current;
	t_iterable	current_copy;

	result = NULL;
	set_iterable(&current, data->tokens);
	while (current.node)
	{
		current_copy.content = ft_strdup(current.content);
		if (!current_copy.content)
			error_exit(MALLOC, data);
		current_copy.token = ft_calloc(1, sizeof(t_token));
		if (!current_copy.token)
			return (free(current_copy.content), error_exit(MALLOC, data), NULL);
		current_copy.token->content = current_copy.content;
		current_copy.token->type = current.token->type;
		current_copy.node = list_new(current_copy.token);
		if (!current_copy.node)
		{
			free(current_copy.content);
			free(current_copy.token);
			error_exit(MALLOC, data);
		}
		list_add_back(&result, current_copy.node);
		set_iterable(&current, current.node->next);
	}
	return (result);
}

// {
// 	t_list	*result;
// 	t_list	*tmp;
// 	t_token	*content_copy;
// 	t_iterable	current;

// 	result = NULL;
// 	current.node = tokens;
// 	while (current.node)
// 	{
// 		content_copy = malloc(sizeof(t_token));
// 		if (!content_copy)
// 		{
// 			list_clear(&result, free_token);
// 			return (NULL);
// 		}
// 		content_copy->content = ft_strdup(current.token->content);
// 		content_copy->type = current.token->type;
// 		tmp = list_new(content_copy);
// 		if (!tmp)
// 		{
// 			list_clear(&result, free_token);
// 			return (NULL);
// 		}
// 		list_add_back(&result, tmp);
// 		current.node = current.node->next;
// 	}
// 	return (result);
// }

// void	init_ast(t_data *data)
// {
// 	data->ast = malloc(sizeof(t_tree));
// 	if (data->ast == NULL)
// 		error_exit(MALLOC, data);
// 	data->ast->content = copy_tokens(data);
// 	data->ast->left = NULL;
// 	data->ast->right = NULL;
// }

// void	tree_print_rec(t_tree *tree, int *tab_count)

// void	tree_print(t_tree *tree)
// {
// 	int	tab_count;

// 	tab_count = 0;
// 	tree_print_rec(tree, &tab_count);
// }


// void	tree_clear(t_tree *tree)
// {
// 	if (tree == NULL)
// 		return ;
// 	if (tree->left == NULL && tree->right == NULL)
// 	{
// 		list_clear(tree->content, free_token);
// 		free(tree);
// 		return ;
// 	}
// 	tree_clear(&tree->left);
// 	tree_clear(&tree->right);
// 	list_clear(tree->content, free_token);
// 	free(tree);
// }

// t_list	*sub_tokens(t_list *tokens, t_list *node, int list_size)
// {
// 	int		i;
// 	t_list	*current;
// 	t_list	*result;
// 	t_list	*tmp;
// 	t_token	*content_copy;
// 	t_iterable	current;
// 	t_iterable	current_copy;

// 	i = 0;
// 	result = NULL;
// 	current = tokens;
// 	if (!tokens || !node || list_size <= 0)
// 		return (NULL);
// 	while (current && current != node)
// 		current = current->next;
// 	if (!current)
// 		return (NULL);
// 	while (i < list_size && current)
// 	{
// 		content_copy->content = ft_strdup(current->content->content);
// 		token->type = current->content->type;
// 		tmp = list_new(token);
// 		if (!tmp)
// 		{
// 			list_clear(&result, free);
// 			return (NULL);
// 		}
// 		list_add_back(&result, tmp);
// 		current = current->next;
// 		i++;
// 	}
// 	return (result);
// }

// int	main(void)
// {
// 	t_data	data;

// 	ft_bzero(&data, sizeof(t_data));
// 	while (1)
// 	{
// 		data.input = readline("minishell> ");
// 		if (data.input == NULL)
// 			ft_putendl_fd("readline error", 2);
// 		else
// 		{
// 			if (ft_strcmp(data.input, "exit") == 0)
// 				break ;
// 			if (data.input[0] != '\0' && !ft_strisspace(data.input))
// 				add_history(data.input);
// 			get_tokens(&data);

// 			init_ast(&data);
// 			// print_tree(data.ast);

// 			free(data.input);
// 			list_print(data.tokens, print_token);
// 			list_print(data.ast->content, print_token);
// 			list_clear(&data.tokens, free_token);
// 			tree_clear(data.ast);
// 		}
// 	}
// 	return (free_all(&data), 0);
// }




// int main()
// {
// 	// les nodes de l'aarbre
// 	t_tree *node_1 = malloc(sizeof(t_tree));
// 	t_tree *node_2 = malloc(sizeof(t_tree));
// 	t_tree *node_3 = malloc(sizeof(t_tree));

// 	// les content des nodes de l'arbre
// 	t_list	*list_1 = NULL;
// 	t_list	*list_2 = NULL;
// 	t_list	*list_3 = NULL;

// 	// les content des nodes des listes
// 	t_token	*token_1 = malloc(sizeof(t_token));
// 	t_token	*token_2 = malloc(sizeof(t_token));
// 	t_token	*token_3 = malloc(sizeof(t_token));
// 	t_token	*token_4 = malloc(sizeof(t_token));
// 	t_token	*token_5 = malloc(sizeof(t_token));
// 	t_token	*token_6 = malloc(sizeof(t_token));

// 	token_1->content = "|";
// 	token_1->type = T_PIPE;
// 	token_2->content = "ls";
// 	token_2->type = T_WORD;
// 	token_3->content = "<";
// 	token_3->type = T_BROKET_LEFT;
// 	token_4->content = "f";
// 	token_4->type = T_WORD;
// 	token_5->content = "-a";
// 	token_5->type = T_WORD;
// 	token_6->content = "cat";
// 	token_6->type = T_WORD;

// 	list_1 = list_new(token_1);
// 	list_2 = list_new(token_2);
// 	list_add_back(&list_2, list_new(token_3));
// 	list_add_back(&list_2, list_new(token_4));
// 	list_add_back(&list_2, list_new(token_5));
// 	list_3 = list_new(token_6);

// 	node_1->content = list_1;
// 	node_2->content = list_2;
// 	node_3->content = list_3;

// 	node_1->left = node_2;
// 	node_1->right = node_3;
// 	node_2->left = NULL;
// 	node_2->right = NULL;
// 	node_3->left = NULL;
// 	node_3->right = NULL;


// }

