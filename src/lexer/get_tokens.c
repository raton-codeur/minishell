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

void	free_token(void *p)
{
	t_token	*token;

	token = p;
	free(token->content);
	free(token);
}

static int	get_char_type(char c)
{
	if (ft_isspace(c))
		return (TOKEN_WHITE_SPACE);
	else if (c == '|')
		return (TOKEN_PIPE);
	else if (c == '>')
		return (TOKEN_BROKET_RIGHT);
	else if (c == '<')
		return (TOKEN_BROKET_LEFT);
	else if (ft_isprint(c))
		return (TOKEN_WORD);
	else
		return (TOKEN_ERROR);
}

static int	go_to_quote_end(char *input, t_get_tokens_utils *u)
{
	char	quote;

	quote = input[u->end];
	u->end++;
	while (input[u->end] && input[u->end] != quote)
		u->end++;
	if (input[u->end] == quote)
		u->end++;
	else
		return (1);
	return (0);
}

static int	go_to_token_end(char *input, t_get_tokens_utils *u)
{
	int	char_type;

	char_type = get_char_type(input[u->end]);
	if (char_type == TOKEN_ERROR)
		return (1);
	else if (char_type != TOKEN_WORD)
	{
		u->current_token_type = char_type;
		u->end++;
	}
	while (char_type == TOKEN_WORD || char_type == TOKEN_WHITE_SPACE)
	{
		u->current_token_type = TOKEN_WORD;
		if (input[u->end] == '\'' || input[u->end] == '"')
			go_to_quote_end(input, u);
		else
			u->end++;
		char_type = get_char_type(input[u->end]);
	}
	return (0);
}

int	get_tokens(t_list **tokens, char *input)
{
	t_get_tokens_utils	u;

	ft_bzero(&u, sizeof(t_get_tokens_utils));
	while (input[u.end] && get_char_type(input[u.end]) == TOKEN_WHITE_SPACE)
		u.end++;
	while (input[u.end])
	{
		if (go_to_token_end(input, &u) || add_token(tokens, input, &u))
			return (list_clear(tokens, free_token), 1);
	}
	return (0);
}
