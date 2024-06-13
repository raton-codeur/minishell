/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:02:03 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/13 14:58:18 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	set_iterable(t_iterable *i, t_list *node)
{
	if (node == NULL)
	{
		ft_bzero(i, sizeof(t_iterable));
		return ;
	}
	i->node = node;
	i->token = node->content;
	i->content = i->token->content;
	i->type = i->token->type;
}

void	set_iterables(t_iterable *current, t_iterable *next, t_list *node)
{
	set_iterable(current, node);
	if (node && next)
		set_iterable(next, node->next);
}

void	remove_node_and_update(\
	t_data *data, t_iterable *current, t_iterable *next)
{
	t_list		*tmp;

	tmp = current->node;
	set_iterables(current, next, current->node->next);
	list_remove_node(&data->tokens, tmp, free_token);
}
