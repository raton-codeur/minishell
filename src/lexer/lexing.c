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

int	list_remove(t_list **list, t_list *node)
{
	t_list	*current;
	t_list	*tmp;

	if (*list == node)
	{
		*list = node->next;
		(*list)->previous = NULL;
		free_token(node->content);
		free(node);
		return (0);
	}
	current = *list;
	while (current->next != node)
		current = current->next;
	tmp = current->next;
	current->next = current->next->next;
	if (current->next)
		current->next->previous = current;
	free_token(tmp->content);
	free(tmp);
	return (0);
}



void	analyze_broket_right(t_list *node)
{
	t_token	*token;
	t_token	*token_next;

	token = node->content;
	if (token->type == TOKEN_BROKET_RIGHT && node->next)
	{
		token_next = node->next->content;
		if (token_next->type == TOKEN_WORD)
			token_next->type = TOKEN_FILE;
	}
}

void	analyze_broket_left(t_list *node)
{
	t_token	*token;
	t_token	*token_next;

	token = node->content;
	if (token->type == TOKEN_BROKET_LEFT && node->next)
	{
		token_next = node->next->content;
		if (token_next->type == TOKEN_WORD)
			token_next->type = TOKEN_FILE;
	}
}

void	analyze_double_brocket_right(t_list *node)
{
	t_token	*token;
	t_token	*token_next;

	token = node->content;
	if (token->type == TOKEN_DOUBLE_BROKET_RIGHT && node->next)
	{
		token_next = node->next->content;
		if (token_next->type == TOKEN_WORD)
			token_next->type = TOKEN_FILE;
	}
}

void	analyze_double_brocket_left(t_list *node)
{
	t_token	*token;
	t_token	*token_next;

	token = node->content;
	if (token->type == TOKEN_DOUBLE_BROKET_LEFT && node->next)
	{
		token_next = node->next->content;
		if (token_next->type == TOKEN_WORD)
			token_next->type = TOKEN_DELIMITER;
	}
}




int	analyze_brokets(t_list **tokens)
{
	t_list	*current;

	current = *tokens;
	while (current)
	{
		analyze_broket_right(current);
		analyze_broket_left(current);
		analyze_double_brocket_right(current);
		analyze_double_brocket_left(current);
		current = current->next;
	}
	return (0);
}



/* token word -> nom de fichier / commande / delimiter*/
void	specialize_words(t_list **tokens)
{
	analyze_brokets(tokens);
	// get_commands(tokens);
}

/*
specialize_word( ps tokens)
remplacer les tokens word par des tokens nom de fichier / commande / delimiter
	change_word_to_file(&tokens);

check words (ps tokens) : 1 si erreur, 0 sinon
verifier quun nom de fichier suit < > et >>
verifier quun delimiter suit <<
verifier quil ny a plus de word ?

si on  a deux brokets de meme type qui se suivent il faut supprmer la premiere
*/

int	lexing(t_list **tokens)
{
	chevron_to_double_chevron(tokens); // fusionner les chevrons simples de meme sens qui se suivent	
	specialize_words(tokens); // word -> nom de fichier / commande / delimiter
	// a ce niveau il ne devrait plus y avoir de token word
	// if (check_words(tokens))
		// return (1);
	// supprimer les quotes et etendre les variables
	return (0);





}

// int	lexing(t_list **tokens)
// {
// 	(void)tokens;
// 	return (0);
// }


