/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:02:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/22 18:03:05 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	add_token(t_list **tokens, char *input, t_get_tokens_utils *u)
{
	t_token	*token;
	t_list	*node;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (1);
	token->content = ft_substr(input, u->start, u->end - u->start);
	u->start = u->end;
	if (token->content == NULL)
		return (free(token), 1);
	token->type = u->current_token_type;
	node = list_new(token);
	if (node == NULL)
		return (free_token(token), 1);
	list_add_back(tokens, node);
	return (0);
}
