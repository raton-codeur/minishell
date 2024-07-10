/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:30:49 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/10 21:29:34 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_double_brokets(t_data *data)
{
	change_double_type(data, T_BROKET_LEFT, "<<", T_DOUBLE_BROKET_LEFT);
	change_double_type(data, T_BROKET_RIGHT, ">>", T_DOUBLE_BROKET_RIGHT);
}

void	get_words(t_data *data)
{
	change_all_type(data, T_DELIMITER, T_WORD);
	merge_type(data, T_CHARACTER);
	change_all_type(data, T_CHARACTER, T_WORD);
	remove_all_by_type(data, T_DOUBLE_QUOTE);
	remove_all_by_type(data, T_SIMPLE_QUOTE);
	remove_all_by_type(data, T_WHITE_SPACE);
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
