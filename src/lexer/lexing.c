/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:20:43 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/24 13:42:34 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	remove_white_space(t_list **tokens)
{
	t_list	*current;
	t_list	*tmp;

	current = *tokens;
	while (current)
	{
		if (((t_token *)current->content)->type == TOKEN_WHITE_SPACE)
		{
			tmp = current;
			current = current->next;
			list_remove_node(tokens, tmp, free_token);
		}
		else
			current = current->next;
	}
}

static	void	words_to_commands(t_list **tokens)
{
	t_list	*current;
	t_token	*token;

	current = *tokens;
	while (current)
	{
		token = current->content;
		if (token->type == TOKEN_WORD)
			token->type = TOKEN_COMMAND;
		current = current->next;
	}
}

static void	specialize_words(t_list **tokens)
{
	analyze_brokets(tokens);
	words_to_commands(tokens);
}

int	lexing(t_list **tokens)
{
	broket_to_double_broket(tokens);
	remove_white_space(tokens);
	specialize_words(tokens);
	if (split_file_tokens(tokens)
		|| expand_variables(tokens)
		// || remove_quotes(tokens)
		)
		return (1);
	// if (check_syntax(*tokens))
	// 	return (1);
	return (0);
}
