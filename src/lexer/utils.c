/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:52:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/11 15:10:11 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	*save(void *p, t_data *data)
{
	if (save_add(p, &data->to_free))
	{
		ft_putendl_fd("malloc error", 2);
		return (free_all(data), exit(1), NULL);
	}
	return (p);
}

void	free_node(void *node_address)
{
	t_list	*node;

	node = node_address;
	free(node->content);
	free(node);
}

void	free_save(void *p, t_data *data)
{
	t_list	*node;

	node = data->to_free;
	while (node)
	{
		if (node->content == p)
		{
			list_remove_node(&data->to_free, node, free_node);
			return ;
		}
		node = node->next;
	}
}

void	free_all(t_data *data)
{
	list_clear(&data->to_free, free);
	list_clear(&data->tokens, free_node);
	free(data->input);
	clear_history();
}

void	error_exit(int code, t_data *data)
{
	if (code == MALLOC)
		ft_putendl_fd(MALLOC_MSG, 2);
	free_all(data);
	exit(code);
}
