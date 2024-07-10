/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:20:43 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/10 13:33:43 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	get_double_brokets(t_data *data)
{
	change_double_type(data, T_BROKET_LEFT, "<<", T_DOUBLE_BROKET_LEFT);
	change_double_type(data, T_BROKET_RIGHT, ">>", T_DOUBLE_BROKET_RIGHT);
}

static void	get_words(t_data *data)
{
	merge_type(data, T_CHARACTER);
	change_type(data, T_CHARACTER, T_WORD);
	remove_by_type(data, T_DOUBLE_QUOTE);
	remove_by_type(data, T_SIMPLE_QUOTE);
	remove_by_type(data, T_WHITE_SPACE);
}

static void	parse_brokets(t_data *data)
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

void	parsing(t_data *data)
{
	init_tokens(data);
	parse_quotes(data);
	get_double_brokets(data);
	parse_delimiters(data);
	expand_variables(data);
	remove_quotes(data);
	get_words(data);
	parse_brokets(data);

	list_print(data->tokens, print_token);
}
