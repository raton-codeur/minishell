/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:30:49 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/10 23:18:23 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_double_brokets(t_data *data)
{
	change_all_consecutive(data, T_BROKET_LEFT, "<<", T_DOUBLE_BROKET_LEFT);
	change_all_consecutive(data, T_BROKET_RIGHT, ">>", T_DOUBLE_BROKET_RIGHT);
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
				|| current.type == T_DOUBLE_QUOTE
				|| current.type == T_SIMPLE_QUOTE
				|| current.type == T_DOLLAR)
			{
				current.token->type = T_DELIMITER;
				set_iterable(&current, current.node->next);
			}
		}
		else
			set_iterable(&current, current.node->next);
	}
	merge_type(data, T_DELIMITER);
	change_all_type(data, T_DELIMITER, T_WORD);
}

void	parse_brokets(t_data *data)
{
	t_iterable	current;
	t_iterable	next;

	set_iterables(&current, &next, data->tokens);
	while (current.node)
	{
		if (current.type == T_BROKET_LEFT
			|| current.type == T_BROKET_RIGHT
			|| current.type == T_DOUBLE_BROKET_LEFT
			|| current.type == T_DOUBLE_BROKET_RIGHT)
		{
			if (next.node == NULL)
				return (syntax_error("newline", data));
			else if (next.type != T_WORD)
				return (syntax_error(next.content, data));
		}
		set_iterables(&current, &next, current.node->next);
	}
}
