/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:26:53 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/11 22:25:50 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_quote(t_iterable i)
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

void	get_char_in_quotes(t_data *data)
{
	t_iterable	current;
	char		quote;

	quote = 0;
	set_iterable(&current, data->tokens);
	while (current.node)
	{
		if (quote == 0 && get_quote(current))
		{
			quote = get_quote(current);
			set_iterable(&current, current.node->next);
			while (get_quote(current) != quote)
			{
				current.token->type = T_CHARACTER;
				set_iterable(&current, current.node->next);
			}
			set_iterable(&current, current.node->next);
			quote = 0;
		}
		else
			set_iterable(&current, current.node->next);
	}
}

static void	find_dollars_in_double_quotes(t_data *data)
{
	t_iterable	current;
	char		quote;

	quote = 0;
	set_iterable(&current, data->tokens);
	while (current.node)
	{
		if (quote == 0 && get_quote(current))
			quote = get_quote(current);
		else if (quote == '\'' && get_quote(current) == '\'')
			quote = 0;
		else if (quote == '"' && get_quote(current) == '"')
			quote = 0;
		else if (quote == '"' && current.content[0] == '$')
			current.token->type = T_DOLLAR;
		set_iterable(&current, current.node->next);
	}
}

void	parse_quotes(t_data *data)
{
	if (!quotes_are_closed(data))
		return (print_error(QUOTE), reset_input(data));
	get_char_in_quotes(data);
	find_dollars_in_double_quotes(data);
	change_all_consecutive(data, T_SIMPLE_QUOTE, "", T_CHARACTER);
	change_all_consecutive(data, T_DOUBLE_QUOTE, "", T_CHARACTER);
}
