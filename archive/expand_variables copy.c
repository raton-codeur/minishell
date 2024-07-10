/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:17 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/10 16:30:22 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

static void	find_variables(t_data *data)
{
	t_iterable	current;
	char		*new_content;

	set_iterable(&current, data->tokens);
	while (current.node)
	{
		if (current.type == T_VARIABLE)
		{
			if (!in_env(current.content, data))
				new_content = ft_strdup("");
			else
				new_content = ft_strdup(get_value(in_env(current.content, data)));
			if (!new_content)
				error_exit(MALLOC, data);
			free(current.content);
			current.token->content = new_content;
			current.token->type = T_CHARACTER;
			if (ft_strcmp(current.token->content, "") == 0)
				remove_and_update(data, &current, NULL);
			else
				set_iterable(&current, current.node->next);
		}
		else
			set_iterable(&current, current.node->next);
	}
}

static void	set_to_variable(t_iterable *current, t_iterable *next)
{
	while (current->node && ft_isword_content(current->content[0]))
	{
		current->token->type = T_VARIABLE;
		set_iterables(current, next, next->node);
	}
}

/* regarder dans exit.c ... */
static char	*get_exit_status(t_data *data)
{
	char	*result;

	result = ft_itoa(data->exit_status);
	if (result == NULL)
		error_exit(MALLOC, data);
	return (result);
}


void	expand_variables(t_data *data)
{
	t_iterable	current;
	t_iterable	next;
	char		*new_content;

	find_variables(data);
	set_iterables(&current, &next, data->tokens);
	while (current.node)
	{
		if (current.type == T_DOLLAR && next.type == T_CHARACTER && (ft_isword_content(next.content[0]) || next.content[0] == '?'))
		{
			remove_and_update(data, &current, &next);
			if (ft_isword_content(current.content[0]))
			{
				if (ft_isword_start(current.content[0]))
					set_to_variable(&current, &next);
				else
					remove_and_update(data, &current, &next);
			}
			else
			{
				new_content = get_exit_status(data);
				if (new_content == NULL)
					error_exit(MALLOC, data);
				change_node(&current.node, new_content, T_CHARACTER, data);
				free(new_content);
				set_iterables(&current, &next, current.node->next);
			}
		}
		else
			set_iterables(&current, &next, next.node);
	}
	change_type(data, T_DOLLAR, T_CHARACTER);
	merge_type(data, T_VARIABLE);
}
