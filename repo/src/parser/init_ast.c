/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:19:45 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/25 13:33:49 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	copy_token_content(t_iterable current, t_iterable *current_copy)
{
	current_copy->content = ft_strdup(current.content);
	if (!current_copy->content)
		return (1);
	current_copy->token = mmm_malloc(1 * sizeof(t_token));
	if (!current_copy->token)
		return (mmm_free(current_copy->content), 1);
	current_copy->token->content = current_copy->content;
	current_copy->token->type = current.type;
	current_copy->node = list_new(current_copy->token);
	if (!current_copy->node)
	{
		mmm_free(current_copy->content);
		mmm_free(current_copy->token);
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

void	init_ast(t_data *data)
{
	if (data->tokens == NULL)
		return ;
	data->ast = mmm_malloc(1 * sizeof(t_tree));
	if (data->ast == NULL)
		error_exit(MALLOC, data);
	data->ast->content = copy_tokens(\
		data->tokens, list_size(data->tokens), data);
}

t_tree	*tree_new(t_list *tokens, t_data *data)
{
	t_tree	*result;

	result = mmm_malloc(1 * sizeof(t_tree));
	if (result == NULL)
		error_exit(MALLOC, data);
	result->content = tokens;
	return (result);
}
