/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:52:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/13 14:07:15 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// void	*save(void *p, t_data *data)
// {
// 	if (save_add(p, &data->to_free))
// 	{
// 		ft_putendl_fd("malloc error", 2);
// 		return (free_all(data), exit(1), NULL);
// 	}
// 	return (p);
// }

void	free_token(void *p)
{
	t_list	*node;

	node = p;
	free(node->content);
	free(node);
}

// void	free_save(void *p, t_data *data)
// {
// 	t_list	*node;

// 	node = data->to_free;
// 	while (node)
// 	{
// 		if (node->content == p)
// 		{
// 			list_remove_node(&data->to_free, node, free_token);
// 			return ;
// 		}
// 		node = node->next;
// 	}
// }

void	free_all(t_data *data)
{
	list_clear(&data->to_free, free);
	list_clear(&data->tokens, free_token);
	tree_clear(data->ast);
	free(data->input);
	rl_clear_history();
}

static void	free_all_error(t_data *data)
{
	free_all(data);
	tree_clear(data->tree);
}

void	error_exit(int code, t_data *data)
{
	if (code == MALLOC)
		ft_putendl_fd(MALLOC_MSG, 2);
	free_all_error(data);
	exit(code);
}
