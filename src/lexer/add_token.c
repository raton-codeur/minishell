/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:02:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/23 13:13:14 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// int	white_space_is_repeated(t_list **tokens, t_get_tokens_utils *u)
// {
// 	t_token	*last_token;

// 	last_token = list_last(*tokens)->content;
// 	if (last_token->type == TOKEN_WHITE_SPACE
// 		&& u->current_token_type == TOKEN_WHITE_SPACE)
// 		return (1);
// 	return (0);
// }

int	add_token(t_list **tokens, char *input, t_get_tokens_utils *u)
{
	t_token	*token;
	t_list	*node;

	// if (white_space_is_repeated(tokens, u))
	// 	return (0);
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
