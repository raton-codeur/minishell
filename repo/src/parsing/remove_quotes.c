/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:40:48 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/10 22:07:05 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	remove_quotes_delimiters(t_data *data)
{
	t_iterable	current;
	t_iterable	next;
	char		quote;

	quote = 0;
	set_iterables(&current, &next, data->tokens);
	while (current.node)
	{
		if (next.type == T_DELIMITER && quote == 0 && get_quote(next))
		{
			quote = get_quote(next);
			list_remove_node(&data->tokens, next.node, free_token);
			set_iterables(&current, &next, current.node);
		}
		else if (next.type == T_DELIMITER && quote && get_quote(next) == quote)
		{
			quote = 0;
			list_remove_node(&data->tokens, next.node, free_token);
			set_iterables(&current, &next, current.node);
		}
		else
			set_iterables(&current, &next, next.node);
	}
}

void	remove_last_quotes(t_data *data)
{
	char		quote;
	t_iterable	current;
	t_iterable	next;

	change_double_type(data, T_SIMPLE_QUOTE, "", T_CHARACTER);
	change_double_type(data, T_DOUBLE_QUOTE, "", T_CHARACTER);
	quote = 0;
	set_iterables(&current, &next, data->tokens);
	while (current.node)
	{
		if (current.type == T_DELIMITER)
		{
			set_iterables(&current, &next, next.node);
			continue ;
		}
		if (quote == 0 && get_quote(next))
		{
			quote = get_quote(next);
			list_remove_node(&data->tokens, next.node, free_token);
			set_iterables(&current, &next, current.node);
		}
		else if (quote && get_quote(next) == quote)
		{
			quote = 0;
			list_remove_node(&data->tokens, next.node, free_token);
			set_iterables(&current, &next, current.node);
		}
		else
			set_iterables(&current, &next, next.node);
	}
}
