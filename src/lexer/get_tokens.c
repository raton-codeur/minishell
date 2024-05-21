/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:05:48 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/21 17:00:8 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	get_char_type(char c)
{
	if (ft_isspace(c))
		return (TOKEN_WHITE_SPACE);
	else if (c == '|')
		return (TOKEN_PIPE);
	else if (c == '>')
		return (TOKEN_CHEVRON_RIGHT);
	else if (c == '<')
		return (TOKEN_CHEVRON_LEFT);
	else if (ft_isprint(c))
		return (TOKEN_WORD);
	else
		return (TOKEN_ERROR);
}

void	free_token(void *p)
{
	t_token	*token;

	token = p;
	free(token->content);
	free(token);
}

static int	add_token(t_list **tokens, char *input, t_get_tokens_utils *u)
{
	t_token	*token;
	t_list	*node;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (1);
	token->content = ft_substr(input, u->start, u->end - u->start);
	if (token->content == NULL)
		return (free(token), 1);
	token->type = u->current_token_type;
	node = list_new(token);
	if (node == NULL)
		return (free_token(token), 1);
	list_add_back(tokens, node);
	return (0);
}

int	get_tokens(t_list **tokens, char *input)
{
	t_get_tokens_utils	u;

	ft_bzero(&u, sizeof(t_get_tokens_utils));
	while (input[u.end] && get_char_type(input[u.end]) == TOKEN_WHITE_SPACE)
		u.end++;
	u.current_token_type = get_char_type(input[u.end]);
	while (input[u.end])
	{
		while (get_char_type(input[u.end]) == u.current_token_type
			|| get_char_type(input[u.end]) == TOKEN_WHITE_SPACE)
		{
			if (get_char_type(input[u.end]) == TOKEN_ERROR)
				return (list_clear(tokens, free_token), 1);
			u.end++;
		}
		if (add_token(tokens, input, &u))
			return (list_clear(tokens, free_token), 1);
		u.current_token_type = get_char_type(input[u.end]);
		u.start = u.end;
	}
	return (0);
}
