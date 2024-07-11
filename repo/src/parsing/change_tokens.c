/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:02:06 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/11 16:01:44 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	change_all_type(t_data *data, int type, int new_type)
{
	t_iterable	current;

	set_iterable(&current, data->tokens);
	while (current.node)
	{
		if (current.type == type)
			current.token->type = new_type;
		set_iterable(&current, current.node->next);
	}
}

void	remove_all_by_type(t_data *data, int type)
{
	t_list		*tmp;
	t_iterable	current;

	set_iterable(&current, data->tokens);
	while (current.node)
	{
		if (current.type == type)
		{
			tmp = current.node;
			set_iterable(&current, current.node->next);
			list_remove_node(&data->tokens, tmp, free_token);
		}
		else
			set_iterable(&current, current.node->next);
	}
}

void	merge_type(t_data *data, int type)
{
	t_iterable	current;
	t_iterable	next;
	char		*new_content;

	set_iterables(&current, &next, data->tokens);
	while (current.node)
	{
		if (current.type == type)
		{
			while (next.node && next.type == type)
			{
				new_content = ft_strjoin(current.content, next.content);
				if (!new_content)
					error_exit(MALLOC, data);
				free(current.content);
				list_remove_node(&data->tokens, next.node, free_token);
				current.token->content = new_content;
				set_iterables(&current, &next, current.node);
			}
		}
		set_iterables(&current, &next, current.node->next);
	}
}

void	change_all_consecutive(\
	t_data *data, int type, char *new_content, int new_type)
{
	t_iterable	current;
	t_iterable	next;

	set_iterables(&current, &next, data->tokens);
	while (current.node)
	{
		if (next.node && current.type == type && next.type == type)
		{
			new_content = ft_strdup(new_content);
			if (!new_content)
				error_exit(MALLOC, data);
			set_token(current, new_content, new_type);
			list_remove_node(&data->tokens, next.node, free_token);
		}
		set_iterables(&current, &next, current.node->next);
	}
}
