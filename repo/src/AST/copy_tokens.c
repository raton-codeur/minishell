/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:40:02 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/13 14:12:52 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static int	copy_token_content(t_iterable current, t_iterable *current_copy)
{
	current_copy->content = ft_strdup(current.content);
	if (!current_copy->content)
		return (1);
	current_copy->token = ft_calloc(1, sizeof(t_token));
	if (!current_copy->token)
		return (free(current_copy->content), 1);
	current_copy->token->content = current_copy->content;
	current_copy->token->type = current.type;
	current_copy->node = list_new(current_copy->token);
	if (!current_copy->node)
	{
		free(current_copy->content);
		free(current_copy->token);
		return (1);
	}
	return (0);
}

t_list	*copy_tokens(t_list *tokens, int size, t_data *data)
{
	int			i;
	t_list		*result;
	t_iterable	current;
	t_iterable	current_copy;

	if (size == 0 || !tokens)
		return (NULL);
	i = 0;
	result = NULL;
	set_iterable(&current, tokens);
	while (i < size && current.node)
	{
		if (copy_token_content(current, &current_copy))
		{
			list_clear(&result, free_token);
			error_exit(MALLOC, data);
		}
		list_add_back(&result, current_copy.node);
		set_iterable(&current, current.node->next);
		i++;
	}
	return (result);
}
