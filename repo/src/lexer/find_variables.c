/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:17 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/27 13:12:30 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	set_to_variable(t_iterable *current, t_iterable *next)
{
	while (current->node && ft_isword_content(current->content[0]))
	{
		current->token->type = T_VARIABLE;
		set_iterables(current, next, next->node);
	}
}

static char	*get_exit_status(t_data *data)
{
	char	*result;

	result = ft_itoa((unsigned char)data->exit_status);
	if (result == NULL)
		error_exit(MALLOC, data);
	return (result);
}

void	find_variables(t_data *data)
{
	t_iterable	current;
	t_iterable	next;

	set_iterables(&current, &next, data->tokens);
	while (current.node)
	{
		if (current.type == T_DOLLAR && current.node->next
			&& next.type == T_CHARACTER && ft_isword_content(next.content[0]))
		{
			remove_node_and_update(data, &current, &next);
			if (current.content[0] == '?')
			{
				change_node(\
					&current.node, get_exit_status(data), T_CHARACTER, data);
				set_iterables(&current, &next, current.node->next);
			}
			else if (ft_isword_start(current.content[0]))
				set_to_variable(&current, &next);
			else
				remove_node_and_update(data, &current, &next);
		}
		else
			set_iterables(&current, &next, next.node);
	}
	change_type(data, T_DOLLAR, T_CHARACTER);
}
