/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_delimiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:29:09 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/10 15:28:52 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	parse_delimiters(t_data *data)
{
	find_delimiters(data);
	remove_by_type_content(data, T_DELIMITER, "'");
	remove_by_type_content(data, T_DELIMITER, "\"");
	merge_type(data, T_DELIMITER);
}
