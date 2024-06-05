/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brocket_to_double_brocket.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:38:46 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/05 16:23:38 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	double_right_is_possible(t_data *data, t_list *node)
{
	t_token	*next;

	set_token(data, node);
	if (data->l->next)
		next = data->l->next->content;
	else
		return (0);
	return (data->t->type == T_BROKET_RIGHT && next->type == T_BROKET_RIGHT);
}

static int	double_left_is_possible(t_data *data, t_list *node)
{
	t_token	*next;

	set_token(data, node);
	if (data->l->next)
		next = data->l->next->content;
	else
		return (0);
	return (data->t->type == T_BROKET_LEFT && next->type == T_BROKET_LEFT);
}

void	broket_to_double_broket(t_data *data)
{
	set_token(data, data->tokens);
	while (data->l)
	{
		if (double_right_is_possible(data, data->l))
		{
			data->t->type = T_DOUBLE_BROKET_RIGHT;
			list_remove_node(&data->tokens, data->l->next, free_node);
		}
		else if (double_left_is_possible(data, data->l))
		{
			data->t->type = T_DOUBLE_BROKET_LEFT;
			list_remove_node(&data->tokens, data->l->next, free_node);
		}
		set_token(data, data->l->next);
	}
}
