/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:39:25 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/11 23:37:10 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	set_variable(t_iterable *current)
{
	while (current->node && ft_isword_content(current->content[0]))
	{
		current->token->type = T_VARIABLE;
		set_iterable(current, current->node->next);
	}
}

void	find_variables(t_data *data)
{
	t_iterable	current;

	set_iterable(&current, data->tokens);
	while (current.node)
	{
		if (current.type == T_DOLLAR)
		{
			current.token->type = T_VARIABLE;
			set_iterable(&current, current.node->next);
			if (ft_isword_start(current.content[0]))
				set_variable(&current);
			else
			{
				current.token->type = T_VARIABLE;
				set_iterable(&current, current.node->next);
			}
		}
		else
			set_iterable(&current, current.node->next);
	}
}

void	merge_variables(t_data *data)
{
	t_iterable	current;
	t_iterable	next;
	char		*new_content;

	set_iterables(&current, &next, data->tokens);
	while (current.node)
	{
		if (current.type == T_VARIABLE)
		{
			remove_and_update(&current, &next, data);
			while (next.type == T_VARIABLE && next.content[0] != '$')
			{
				new_content = ft_strjoin(current.content, next.content);
				if (!new_content)
					error_exit(MALLOC, data);
				set_token(current, new_content, T_VARIABLE);
				list_remove_node(&data->tokens, next.node, free_token);
				set_iterables(&current, &next, current.node);
			}
		}
		set_iterable(&current, current.node->next);
	}
}
