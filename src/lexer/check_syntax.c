/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:15:58 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/23 15:30:58 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


static int	check_words(t_list *tokens)
{
	t_list	*current;
	t_token	*token;
	t_token	*next_token;

	current = tokens;
	while (current)
	{
		token = current->content;
		if(current->next)
			next_token = current->next->content;
		if (token->type == TOKEN_BROKET_LEFT && next_token->type != TOKEN_FILE)
			return (1);
		if (token->type == TOKEN_BROKET_RIGHT && next_token->type != TOKEN_FILE)
			return (1);
		if (token->type == TOKEN_DOUBLE_BROKET_RIGHT && next_token->type != TOKEN_FILE)
			return (1);	
		if (token->type == TOKEN_DOUBLE_BROKET_LEFT && next_token->type != TOKEN_DELIMITER)
			return (1);
		current = current->next;
	}
	return (0);
}

int	check_syntax(t_list *tokens)
{
	return (check_words(tokens));
}
