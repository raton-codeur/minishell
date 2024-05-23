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






// void	find_delimiters(t_list **tokens)
// {}

// void	fill_commands(t_list **tokens)
// {}

// /* token word -> nom de fichier / commande / delimiter*/
// static	void	words_to_commands(t_list **tokens)
// {
// 	t_list	*current;
// 	t_token	*token;

// 	current = *tokens;
// 	while (current)
// 	{
// 		token = current->content;
// 		if (token->type == TOKEN_WORD)
// 			token->type = TOKEN_COMMAND;
// 		current = current->next;
// 	}
// }
static void	specialize_words(t_list **tokens)
{
	analyze_brokets(tokens);
	// find_delimiters(tokens);
	// fill_commands(tokens);
}

/*
check words (ps tokens) : 1 si erreur, 0 sinon
verifier quun nom de fichier suit < > et >>
verifier quun delimiter suit <<

si on  a deux brokets de meme type qui se suivent il faut supprmer la premiere
*/

int	lexing(t_list **tokens)
{
	broket_to_double_broket(tokens);
	specialize_words(tokens); // word -> nom de fichier / commande / delimiter
	// a ce niveau ya plus de token word
	// if (check_words(tokens))
		// return (1);

	// supprimer les quotes et etendre les variables

	return (0);
}
