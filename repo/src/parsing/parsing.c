/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:20:43 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/11 17:31:14 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"





void	find_single_dollars(t_data *data)
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


void	find_dollars_in_delimiters(t_data *data)
{
	t_iterable	current;
	t_iterable	next;

	set_iterables(&current, &next, data->tokens);
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
			{
				if (current.type == T_DOLLAR)
					current.token->type = T_CHARACTER;
				set_iterable(&current, current.node->next);
			}
		}
		else
			set_iterable(&current, current.node->next);
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
			while (current.type == T_WHITE_SPACE)
				set_iterable(&current, current.node->next);
			while (current.type == T_CHARACTER
				|| current.type == T_SIMPLE_QUOTE
				|| current.type == T_DOUBLE_QUOTE)
			{
				if (current.type == T_CHARACTER)
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

void	parse_dollars(t_data *data)
{
	change_all_consecutive(data, T_BROKET_LEFT, "<<", T_DOUBLE_BROKET_LEFT);
	change_all_consecutive(data, T_BROKET_RIGHT, ">>", T_DOUBLE_BROKET_RIGHT);
	find_delimiters(data);
	find_dollars_in_double_quotes(data);
	find_single_dollars(data);
	find_dollars_in_delimiters(data);
}

void	parsing(t_data *data)
{
	init_tokens(data);
	parse_quotes(data);
	parse_dollars(data);
	expand_variables(data);
	get_words(data);
	parse_brokets(data);
}
