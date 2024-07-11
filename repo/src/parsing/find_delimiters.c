/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_delimiters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:08:36 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/11 23:08:47 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	analyse_delimiter_content(t_iterable *i, t_data *data)
{
	if (i->type == T_CHARACTER || i->type == T_DOLLAR)
	{
		i->token->type = T_DELIMITER;
		set_iterable(i, i->node->next);
	}
	else
		remove_and_update(i, NULL, data);
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
			while (current.type == T_WHITE_SPACE)
				set_iterable(&current, current.node->next);
			while (current.type == T_CHARACTER
				|| current.type == T_DOLLAR
				|| current.type == T_SIMPLE_QUOTE
				|| current.type == T_DOUBLE_QUOTE)
				analyse_delimiter_content(&current, data);
		}
		else
			set_iterable(&current, current.node->next);
	}
}
