/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_delimiters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:08:36 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/13 16:31:43 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	analyse_delimiter(t_iterable *current, t_data *data)
{
	while (current->type == T_WHITE_SPACE)
		set_iterable(current, current->node->next);
	while (current->type == T_CHARACTER
		|| current->type == T_DOLLAR
		|| current->type == T_SIMPLE_QUOTE
		|| current->type == T_DOUBLE_QUOTE)
	{
		if (current->type == T_CHARACTER || current->type == T_DOLLAR)
		{
			current->token->type = T_DELIMITER;
			set_iterable(current, current->node->next);
		}
		else
			remove_and_update(current, NULL, data);
	}
}

void	find_delimiters(t_data *data)
{
	t_iterable	current;

	set_iterable(&current, data->tokens);
	while (current.node)
	{
		if (current.type == T_DOUBLE_BROKET_LEFT)
		{
			set_iterable(&current, current.node->next);
			analyse_delimiter(&current, data);
		}
		else
			set_iterable(&current, current.node->next);
	}
}
