/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:52:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/14 16:34:27 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


// /*
// s = save(ft_strdup("test"), data)
// */
// void	*save(void *p, t_data *data)
// {
// 	if (save_add(p, &data->to_free))
// 	{
// 		ft_putendl_fd("malloc error", 2);
// 		return (free_all(data), exit(1), NULL);
// 	}
// 	return (p);
// }

// /*
// free_save(s, data)
// */
// void	free_save(void *p, t_data *data)
// {
// 	t_list	*node;

// 	node = data->to_free;
// 	while (node)
// 	{
// 		if (node->content == p)
// 		{
// 			list_remove_node(&data->to_free, node, free_node);
// 			return ;
// 		}
// 		node = node->next;
// 	}
// }

void	free_token(void *p)
{
	t_list	*token;

	token = p;
	free(token->content);
	free(token);
}

void	tree_clear(t_tree **tree)
{
	if (*tree == NULL)
		return ;
	tree_clear(&(*tree)->left);
	tree_clear(&(*tree)->right);
	list_clear((t_list **)&(*tree)->content, free_token);
	free(*tree);
	*tree = NULL;
}

void	free_all(t_data *data)
{
	// list_clear(&data->to_free, free);
	list_clear(&data->tokens, free_token);
	tree_clear(&data->ast);
	free(data->input);
	rl_clear_history();
}

static void	free_all_error(t_data *data)
{
	free_all(data);
	tree_clear(&data->tree);
}

void	error_exit(int code, t_data *data)
{
	if (code == MALLOC)
		ft_putendl_fd(MALLOC_MSG, 2);
	free_all_error(data);
	exit(code);
}



// void set_error(t_data *data, int code, char *message)
// {
// 	data->error.code = code;
// 	data->error.message = message;
// }

void	syntax_error(t_data *data, int code, char *token)
{
	char	*message;
	char	*to_free;

	message = ft_strjoin("syntax error near unexpected token `", token);
	if (!message)
		error_exit(MALLOC, data);
	to_free = message;
	message = ft_strjoin(message, "'");
	free(to_free);
	if (!message)
		error_exit(MALLOC, data);
	free(data->error.message);
	data->error.message = message;
	data->error.code = code;
}

void	reset_error(t_data *data)
{
	data->error.code = 0;
	free(data->error.message);
	data->error.message = NULL;
}
