/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:30:49 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/13 23:18:59 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_double_brokets(t_data *data)
{
	change_all_consecutive(data, T_BROKET_LEFT, "<<", T_DOUBLE_BROKET_LEFT);
	change_all_consecutive(data, T_BROKET_RIGHT, ">>", T_DOUBLE_BROKET_RIGHT);
}

void	find_last_dollar_chars(t_data *data)
{
	t_iterable	current;
	t_iterable	next;

	set_iterables(&current, &next, data->tokens);
	while (current.node)
	{
		if (current.type == T_DOLLAR
			&& next.type != T_CHARACTER
			&& next.type != T_DOLLAR)
			current.token->type = T_CHARACTER;
		if (current.type == T_DOLLAR && get_quote(next))
			current.token->type = T_CHARACTER;
		set_iterables(&current, &next, current.node->next);
	}
}

void	get_words(t_data *data)
{
	get_char_in_quotes(data);
	remove_all_by_type(data, T_SIMPLE_QUOTE);
	remove_all_by_type(data, T_DOUBLE_QUOTE);
	merge_type(data, T_DELIMITER);
	change_all_type(data, T_DELIMITER, T_WORD);
	merge_type(data, T_CHARACTER);
	change_all_type(data, T_CHARACTER, T_WORD);
	remove_all_by_type(data, T_WHITE_SPACE);
}

void	parse_brokets(t_data *data)
{
	t_iterable	current;
	t_iterable	next;

	set_iterables(&current, &next, data->tokens);
	while (current.node)
	{
		if (get_broket(current.node))
		{
			if (next.node == NULL)
				return (syntax_error("newline", data));
			else if (next.type != T_WORD)
				return (syntax_error(next.content, data));
		}
		set_iterables(&current, &next, current.node->next);
	}
}
