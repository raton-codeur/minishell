/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_delimiters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:08:36 by qhauuy            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/13 16:10:51 by qhauuy           ###   ########.fr       */
=======
/*   Updated: 2024/07/11 23:17:53 by qhauuy           ###   ########.fr       */
>>>>>>> 31260249afa83f1a2005fc9e3ad180e4a67731c3
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

<<<<<<< HEAD
static void	analyse_delimiter(t_iterable *current, t_data *data)
{
	while (current->type == T_WHITE_SPACE)
		set_iterable(current, current->node->next);
	while (current->type == T_CHARACTER
		|| current->type == T_DOLLAR
		|| current->type == T_SIMPLE_QUOTE
		|| current->type == T_DOUBLE_QUOTE)
	{
		if (current->type == T_CHARACTER || current->type == T_DOLLAR)
		{
			current->token->type = T_DELIMITER;
			set_iterable(current, current->node->next);
		}
		else
			remove_and_update(current, NULL, data);
	}
=======
static void	analyse_delimiter_content(t_iterable *i, t_data *data)
{
	if (i->type == T_CHARACTER || i->type == T_DOLLAR)
	{
		i->token->type = T_DELIMITER;
		set_iterable(i, i->node->next);
	}
	else
		remove_and_update(i, NULL, data);
>>>>>>> 31260249afa83f1a2005fc9e3ad180e4a67731c3
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
<<<<<<< HEAD
			analyse_delimiter(&current, data);
=======
			while (current.type == T_WHITE_SPACE)
				set_iterable(&current, current.node->next);
			while (current.type == T_CHARACTER
				|| current.type == T_DOLLAR
				|| current.type == T_SIMPLE_QUOTE
				|| current.type == T_DOUBLE_QUOTE)
				analyse_delimiter_content(&current, data);
>>>>>>> 31260249afa83f1a2005fc9e3ad180e4a67731c3
		}
		else
			set_iterable(&current, current.node->next);
	}
}
