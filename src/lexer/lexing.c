/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:20:43 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/22 15:56:110 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	remove_white_space(t_list **tokens)
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
	return (0);
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



/*

si on  a deux brokets de meme type qui se suivent dans une expression il faut supprmer la premiere
gestion double << a la suite a voir 



si on a un pipe il faut deux expression avant et apres

*/

void	brokets_remove_if_double(t_list **tokens)
{
	t_list *current;
	t_token *token;
	int brockets_find;

	current = *tokens;
	brockets_find = 0;
	while (current)
	{
		token = current->content;
		if (token->type == TOKEN_BROKET_LEFT || token->type == TOKEN_BROKET_RIGHT || token->type == TOKEN_BROKET_DOUBLE_LEFT || token->type == TOKEN_BROKET_DOUBLE_RIGHT)
		{
			if (brockets_find == 1)
			{
				brockets_find = 0;
				list_remove_node(tokens, current, free_token);
			}
			else
				brockets_find = 1;
		}
		else
			brockets_find = 0;
		{
			/* code */
		}
		
		current = current->next;
	}
	
}

int	lexing(t_list **tokens)
{
	broket_to_double_broket(tokens);
	remove_white_space(tokens);
	specialize_words(tokens); // word -> nom de fichier / commande / delimiter ==> plus de token WORD
	split_file_tokens(tokens);

	expand_variables(tokens);
	remove_quotes(tokens);


	if (check_syntax(*tokens))
		return (1);


	return (0);
}
