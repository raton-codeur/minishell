/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:15:58 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/08 22:55:47 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// static int	check_words(t_list *tokens)
// {
// 	t_list	*current;
// 	t_token	*token;
// 	t_token	*next_token;

// 	current = tokens;
// 	while (current)
// 	{
// 		token = current->content;
// 		if (current->next)
// 			next_token = current->next->content;
// 		if (token->type == TOKEN_BROKET_LEFT && next_token->type != TOKEN_FILE)
// 			return (1);
// 		if (token->type == TOKEN_BROKET_RIGHT && next_token->type != TOKEN_FILE)
// 			return (1);
// 		if (token->type == TOKEN_DOUBLE_BROKET_RIGHT
// 			&& next_token->type != TOKEN_FILE)
// 			return (1);
// 		if (token->type == TOKEN_DOUBLE_BROKET_LEFT
// 			&& next_token->type != TOKEN_DELIMITER)
// 			return (1);
// 		current = current->next;
// 	}
// 	return (0);
// }

/*

si on  a deux brokets de meme type qui se suivent dans une expression il faut supprmer la premiere
gestion double << a la suite a voir



si on a un pipe il faut deux expression avant et apres

*/

// int	check_syntax(t_list *tokens)
// {
// 	return (check_words(tokens));
// }
