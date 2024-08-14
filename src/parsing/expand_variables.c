/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:17 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/11 17:48:24 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_token	*get_new_token(char	*new_content)
{
	t_token	*result;

	result = ft_calloc(1, sizeof(t_token));
	if (result == NULL)
		return (NULL);
	result->content = new_content;
	if (ft_isspace(new_content[0]))
		result->type = T_WHITE_SPACE;
	else
		result->type = T_CHARACTER;
	return (result);
}

static t_list	*get_new_tokens(char *s)
{
	t_list		*result;
	int			i;
	t_iterable	new;

	result = NULL;
	i = 0;
	while (s && s[i])
	{
		new.content = ft_calloc(2, sizeof(char));
		if (new.content == NULL)
			return (list_clear(&result, free_token), NULL);
		new.content[0] = s[i];
		new.token = get_new_token(new.content);
		if (new.token == NULL)
			return (list_clear(&result, free_token), free(new.content), NULL);
		new.node = list_new(new.token);
		if (new.node == NULL)
		{
			list_clear(&result, free_token);
			return (free_token(new.token), NULL);
		}
		list_add_back(&result, new.node);
		i++;
	}
	return (result);
}

static void	insert_value(t_iterable *current, t_data *data)
{
	char	*value;
	t_list	*to_insert;

	value = get_value(in_env(current->content, data));
	if (value[0] == '\0')
		return (remove_and_update(current, NULL, data));
	to_insert = get_new_tokens(value);
	if (to_insert == NULL)
		return (error_exit(MALLOC, data));
	list_last(to_insert)->next = current->node->next;
	if (current->node->next)
		current->node->next->previous = list_last(to_insert);
	to_insert->previous = current->node;
	current->node->next = to_insert;
	remove_and_update(current, NULL, data);
}

static void	expand_variable(t_iterable *current, t_data *data)
{
	char	*new_content;

	if (current->content[0] == '?')
	{
		new_content = ft_itoa((unsigned char)g_exit_status);
		if (new_content == NULL)
			error_exit(MALLOC, data);
		set_token(*current, new_content, T_CHARACTER);
		set_iterable(current, current->node->next);
	}
	else if (!(ft_isword_start(current->content[0]))
		|| !get_value(in_env(current->content, data)))
		remove_and_update(current, NULL, data);
	else
		insert_value(current, data);
}

void	expand_variables(t_data *data)
{
	t_iterable	current;

	find_variables(data);
	merge_variables(data);
	set_iterable(&current, data->tokens);
	while (current.node)
	{
		if (current.type == T_VARIABLE)
			expand_variable(&current, data);
		else
			set_iterable(&current, current.node->next);
	}
}
