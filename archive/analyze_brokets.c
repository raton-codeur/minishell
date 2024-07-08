/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_brokets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:04:17 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/08 22:55:47 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void	analyze_broket_right(t_list *node)
// {
// 	t_token	*token;
// 	t_token	*token_next;

// 	token = node->content;
// 	if (token->type == TOKEN_BROKET_RIGHT && node->next)
// 	{
// 		token_next = node->next->content;
// 		if (token_next->type == TOKEN_WORD)
// 			token_next->type = TOKEN_FILE;
// 	}
// }

// void	analyze_broket_left(t_list *node)
// {
// 	t_token	*token;
// 	t_token	*token_next;

// 	token = node->content;
// 	if (token->type == TOKEN_BROKET_LEFT && node->next)
// 	{
// 		token_next = node->next->content;
// 		if (token_next->type == TOKEN_WORD)
// 			token_next->type = TOKEN_FILE;
// 	}
// }

// void	analyze_double_brocket_right(t_list *node)
// {
// 	t_token	*token;
// 	t_token	*token_next;

// 	token = node->content;
// 	if (token->type == TOKEN_DOUBLE_BROKET_RIGHT && node->next)
// 	{
// 		token_next = node->next->content;
// 		if (token_next->type == TOKEN_WORD)
// 			token_next->type = TOKEN_FILE;
// 	}
// }

// void	analyze_double_brocket_left(t_list *node)
// {
// 	t_token	*token;
// 	t_token	*token_next;

// 	token = node->content;
// 	if (token->type == TOKEN_DOUBLE_BROKET_LEFT && node->next)
// 	{
// 		token_next = node->next->content;
// 		if (token_next->type == TOKEN_WORD)
// 			token_next->type = TOKEN_DELIMITER;
// 	}
// }

// void	analyze_brokets(t_list **tokens)
// {
// 	t_list	*current;

// 	current = *tokens;
// 	while (current)
// 	{
// 		analyze_broket_right(current);
// 		analyze_broket_left(current);
// 		analyze_double_brocket_right(current);
// 		analyze_double_brocket_left(current);
// 		current = current->next;
// 	}
// }
