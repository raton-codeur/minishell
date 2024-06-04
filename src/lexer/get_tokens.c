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

static int	get_type(char c)
{
	if (c == '|')
		return (TYPE_PIPE);
	else if (c == '>')
		return (TYPE_BROKET_RIGHT);
	else if (c == '<')
		return (TYPE_BROKET_LEFT);
	else if (c == '\'')
		return (TYPE_SIMPLE_QUOTE);
	else if (c == '"')
		return (TYPE_DOUBLE_QUOTE);
	else if (ft_isspace(c))
		return (TYPE_WHITE_SPACE);
	else if (ft_isprint(c))
		return (TYPE_CHARACTER);
	else
		return (TYPE_ERROR);
}

// static int	go_to_quote_end(char *input, t_get_tokens_utils *u)
// {
// 	char	quote;

// 	quote = input[u->end];
// 	u->end++;
// 	while (input[u->end] && input[u->end] != quote)
// 		u->end++;
// 	if (input[u->end] != quote)
// 		return (1);
// 	return (0);
// }

// static int	go_to_token_end(char *input, t_get_tokens_utils *u)
// {
// 	int	char_type;

// 	char_type = get_char_type(input[u->end]);
// 	u->current_token_type = char_type;
// 	if (char_type == ERROR)
// 		return (1);
// 	else if (char_type == WORD)
// 	{
// 		while (char_type == WORD || char_type == WHITE_SPACE)
// 		{
// 			if ((input[u->end] == '\'' || input[u->end] == '"')
// 				&& go_to_quote_end(input, u))
// 				return (1);
// 			u->end++;
// 			char_type = get_char_type(input[u->end]);
// 		}
// 	}
// 	else
// 		u->end++;
// 	return (0);
// }

// static int	add_token(t_list **tokens, char *input, t_get_tokens_utils *u)
// {
// 	t_token	*token;
// 	t_list	*node;

// 	token = malloc(sizeof(t_token));
// 	if (token == NULL)
// 		return (1);
// 	token->content = ft_substr(input, u->start, u->end - u->start);
// 	u->start = u->end;
// 	if (token->content == NULL)
// 		return (free(token), 1);
// 	token->type = u->current_token_type;
// 	node = list_new(token);
// 	if (node == NULL)
// 		return (free_token(token), 1);
// 	list_add_back(tokens, node);
// 	return (0);
// }

// void	set_token(t_data *data, t_list *node)
// {
// 	data->t = node->content;
// 	data->s = data->t->content;
// }

static void	split_char(t_data *data)
{
	int		i;
	t_list	*node;

	i = 0;
	while (data->input[i])
	{
		data->s = ft_calloc(2, sizeof(char));
		if (data->s == NULL)
			return (free_all(data), exit(1));
		data->s[0] = data->input[i];
		data->t = ft_calloc(1, sizeof(t_token));
		if (data->t == NULL)
			return (free_all(data), exit(1));
		data->t->content = data->s;
		data->t->type = get_type(data->input[i]);
		node = list_new(data->t);
		if (data->s == NULL)
			return (free_all(data), exit(1));
		list_add_back(&data->tokens, node);
		i++;
	}
}

int	get_tokens(t_data *data)
{
	split_char(data);
	
	return (0);
}
