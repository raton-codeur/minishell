/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brocket_to_double_brocket.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:38:46 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/04 21:05:38 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// static int	double_right_is_possible(t_list *node)
// {
// 	t_token	*token_1;
// 	t_token	*token_2;

// 	token_1 = node->content;
// 	if (node->next)
// 		token_2 = node->next->content;
// 	else
// 		return (0);
// 	return (token_1->type == TOKEN_BROKET_RIGHT
// 		&& token_2->type == TOKEN_BROKET_RIGHT);
// }

// static int	double_left_is_possible(t_list *node)
// {
// 	t_token	*token_1;
// 	t_token	*token_2;

// 	token_1 = node->content;
// 	if (node->next)
// 		token_2 = node->next->content;
// 	else
// 		return (0);
// 	return (token_1->type == TOKEN_BROKET_LEFT
// 		&& token_2->type == TOKEN_BROKET_LEFT);
// }

// void	broket_to_double_broket(t_list **tokens)
// {
// 	t_list	*current;

// 	current = *tokens;
// 	while (current)
// 	{
// 		if (double_right_is_possible(current))
// 		{
// 			((t_token *)current->content)->type = TOKEN_DOUBLE_BROKET_RIGHT;
// 			list_remove_node(tokens, current->next, free_token);
// 		}
// 		else if (double_left_is_possible(current))
// 		{
// 			((t_token *)current->content)->type = TOKEN_DOUBLE_BROKET_LEFT;
// 			list_remove_node(tokens, current->next, free_token);
// 		}
// 		current = current->next;
// 	}
// }
