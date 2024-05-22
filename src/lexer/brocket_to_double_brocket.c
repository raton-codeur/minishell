/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brocket_to_double_brocket.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:38:46 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/22 16:06:34 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	double_right_is_possible(t_list *node)
{
	t_token	*token_1;
	t_token	*token_2;

	token_1 = node->content;
	if (node->next)
		token_2 = node->next->content;
	else
		return (0);
	return (token_1->type == TOKEN_BROCKET_RIGHT
		&& token_2->type == TOKEN_BROCKET_RIGHT);
}

static int	double_left_is_possible(t_list *node)
{
	t_token	*token_1;
	t_token	*token_2;

	token_1 = node->content;
	if (node->next)
		token_2 = node->next->content;
	else
		return (0);
	return (token_1->type == TOKEN_BROCKET_LEFT
		&& token_2->type == TOKEN_BROCKET_LEFT);
}

int	broket_to_double_broket(t_list **tokens)
{
	t_list	*current;

	current = *tokens;
	while (current)
	{
		if (double_right_is_possible(current))
		{
			((t_token *)current->content)->type = TOKEN_DOUBLE_BROCKET_RIGHT;
			list_remove(tokens, current->next);
		}
		else if (double_left_is_possible(current))
		{
			((t_token *)current->content)->type = TOKEN_DOUBLE_BROCKET_LEFT;
			list_remove(tokens, current->next);
		}
		current = current->next;
	}
	return (0);
}
