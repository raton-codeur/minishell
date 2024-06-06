/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:20:43 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/06 18:10:22 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	analyse_quotes(t_data *data)
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

void	expand_variables(t_data *data)
{
	t_iterable	current;
	char		*new_content;

	set_iterable(&current, data->tokens);
	while (current.node)
	{
		if (current.type == T_VARIABLE)
		{
			new_content = ft_strdup(getenv(current.content));
			if (!new_content)
				error_exit(MALLOC, data);
			free(current.content);
			current.token->content = new_content;
			current.token->type = T_CHARACTER;
		}
		set_iterable(&current, current.node->next);
	}
}


// void	find_delimiters(t_data *data)
// {
// 	t_iterable	current;
// 	t_iterable	next;

// 	set_iterables(&current, &next, data->tokens);
// 	while (current.node)
// 	{
// 		if (current.type == T_DOUBLE_BROKET_LEFT)
// 		{
// 			while (current.node && current.type == T_WHITE_SPACE)
// 				set_iterables(&current, &next, current.node->next);
// 		}
// 		else
// 			set_iterables(&current, &next, next.node->next);
// 	}

// 	// if (next.node && current.type == T_DOUBLE_BROKET_LEFT)
// 	// 	{
// 	// 		while (next.node && )
// 	// 		{
// 	// 			next.token->type = T_DELIMITER;
// 	// 			set_iterables(&current, &next, next.node->next);
// 	// 		}
// 	// 	}
// }


int	lexing(t_data *data)
{
	if (analyse_quotes(data))
		return (1);
	change_double_type(data, T_BROKET_LEFT, "<<", T_DOUBLE_BROKET_LEFT);
	change_double_type(data, T_BROKET_RIGHT, ">>", T_DOUBLE_BROKET_RIGHT);
	change_double_type(data, T_SIMPLE_QUOTE, "", T_CHARACTER);
	change_double_type(data, T_DOUBLE_QUOTE, "", T_CHARACTER);
	// find_delimiters(data);
	// merge_type(data, T_DELIMITER);
	find_variables(data);
	merge_type(data, T_VARIABLE);
	expand_variables(data);
	merge_type(data, T_CHARACTER);
	change_type(data, T_CHARACTER, T_WORD);
	remove_type(data, T_DOUBLE_QUOTE);
	remove_type(data, T_SIMPLE_QUOTE);
	remove_type(data, T_WHITE_SPACE);
	// check_syntax(data);
	return (0);
}
