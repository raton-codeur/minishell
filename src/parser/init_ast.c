/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:19:45 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/13 10:20:00 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

static t_list	*copy_tokens(t_data	*data)
{
	t_list		*result;
	t_iterable	current;
	t_iterable	current_copy;

	result = NULL;
	set_iterable(&current, data->tokens);
	while (current.node)
	{
		if (copy_token_content(current, &current_copy))
			error_exit(MALLOC, data);
		list_add_back(&result, current_copy.node);
		set_iterable(&current, current.node->next);
	}
	return (result);
}

void	init_ast(t_data *data)
{
	data->ast = malloc(sizeof(t_tree));
	if (data->ast == NULL)
		error_exit(MALLOC, data);
	data->ast->content = copy_tokens(data);
	data->ast->left = NULL;
	data->ast->right = NULL;
}
