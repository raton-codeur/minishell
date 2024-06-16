/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:20:43 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/16 17:13:49 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	analyse_quotes(t_data *data)
{
	char		quote;
	t_iterable	i;

	quote = 0;
	set_iterable(&i, data->tokens);
	while (i.node)
	{
		if (quote == 0)
		{
			if (i.content[0] == '\'' || i.content[0] == '"')
				quote = i.content[0];
		}
		else
		{
			if (i.content[0] == quote)
				quote = 0;
			else if (!(i.content[0] == '$' && quote == '"'))
				i.token->type = T_CHARACTER;
		}
		set_iterable(&i, i.node->next);
	}
	return (quote != 0);
}

static void	expand_variables(t_data *data)
{
	t_iterable	current;
	char		*new_content;

	set_iterable(&current, data->tokens);
	while (current.node)
	{
		if (current.type == T_VARIABLE)
		{
			if (getenv(current.content) == NULL)
				new_content = ft_strdup("");
			else
				new_content = ft_strdup(getenv(current.content));
			if (!new_content)
				error_exit(MALLOC, data);
			free(current.content);
			current.token->content = new_content;
			current.token->type = T_CHARACTER;
			if (ft_strcmp(current.token->content, "") == 0)
				remove_node_and_update(data, &current, NULL);
			else
				set_iterable(&current, current.node->next);
		}
		else
			set_iterable(&current, current.node->next);
	}
}

static void	find_delimiters(t_data *data)
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
}

static int	analyse_brokets(t_data *data)
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
				return (syntax_error("newline", data), 1);
			else if (next.type != T_WORD)
				return (syntax_error(next.content, data), 1);
		}
		set_iterables(&current, &next, current.node->next);
	}
	return (0);
}

int	lexing(t_data *data)
{
	if (analyse_quotes(data))
		return (ft_putendl_fd("quote error", 2), 0);
	change_double_type(data, T_BROKET_LEFT, "<<", T_DOUBLE_BROKET_LEFT);
	change_double_type(data, T_BROKET_RIGHT, ">>", T_DOUBLE_BROKET_RIGHT);
	change_double_type(data, T_SIMPLE_QUOTE, "", T_CHARACTER);
	change_double_type(data, T_DOUBLE_QUOTE, "", T_CHARACTER);
	find_delimiters(data);
	remove_by_type_content(data, T_DELIMITER, "'");
	remove_by_type_content(data, T_DELIMITER, "\"");
	merge_type(data, T_DELIMITER);
	find_variables(data);
	change_type(data, T_DELIMITER, T_WORD);
	merge_type(data, T_VARIABLE);
	expand_variables(data);
	merge_type(data, T_CHARACTER);
	change_type(data, T_CHARACTER, T_WORD);
	remove_by_type(data, T_DOUBLE_QUOTE);
	remove_by_type(data, T_SIMPLE_QUOTE);
	remove_by_type(data, T_WHITE_SPACE);
	if (analyse_brokets(data))
		return (0);
	return (1);
}
