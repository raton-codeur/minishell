/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:21:47 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/23 15:50:02 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_token(void *p)
{
	t_token	*token;

	token = p;
	free(token->content);
	free(token);
}

int	go_to_quote_end(char *input, t_get_tokens_utils *u)
{
	char	quote;

	quote = input[u->end];
	u->end++;
	while (input[u->end] && input[u->end] != quote)
		u->end++;
	if (input[u->end] != quote)
		return (1);
	return (0);
}


