/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:26:53 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/10 13:39:54 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	get_quote(t_iterable i)
{
	if (i.node == NULL)
		return (0);
	if (i.content[0] == '\'' || i.content[0] == '"')
		return (i.content[0]);
	else
		return (0);
}

static int	quotes_are_closed(t_data *data)
{
	char		quote;
	t_iterable	current;

	quote = 0;
	set_iterable(&current, data->tokens);
	while (current.node)
	{
		if (quote == 0 && get_quote(current))
			quote = get_quote(current);
		else if (quote && get_quote(current) == quote)
			quote = 0;
		set_iterable(&current, current.node->next);
	}
	return (quote == 0);
}

static void	change_inner_types(t_data *data)
{
	char		quote;
	t_iterable	current;

	quote = 0;
	set_iterable(&current, data->tokens);
	while (current.node)
	{
		if (quote == 0 && get_quote(current))
			quote = get_quote(current);
		else if (quote)
		{
			if (get_quote(current) == quote)
				quote = 0;
			if (!(current.content[0] == '$' && quote == '\''))
				current.token->type = T_CHARACTER;
		}
		set_iterable(&current, current.node->next);
	}
}

void	parse_quotes(t_data *data)
{
	if (!quotes_are_closed(data))
		return (print_error(QUOTE), reset_input(data));
	change_inner_types(data);
}

void	remove_quotes(t_data *data)
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
