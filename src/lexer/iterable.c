/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:02:03 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/11 15:22:23 by qhauuy           ###   ########.fr       */
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
	if (node)
		set_iterable(next, node->next);
}

void	remove_node_and_update(\
	t_data *data, t_iterable *current, t_iterable *next)
{
	t_list		*tmp;

	tmp = current->node;
	set_iterables(current, next, next->node);
	list_remove_node(&data->tokens, tmp, free_node);
}
