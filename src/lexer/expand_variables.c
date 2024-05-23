/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:56:37 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/23 16:51:111 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*

get value (c : un content de token de node a partir dune variable correcte ) : la valeur de la variable avec getenv
	faire get env de c
	si 


int	expand_variables(t_list **tokens) : 1 si erreur 0 sinon
	node = *tokens
	while (node)
		token = node->content
		content = token->content
		si ((token->type == FILE ou COMMAND) et (expand_variables_token(pointeur sur content))
			return 1
		node = node->next
	return 0
*/






int	find_dollar(char *s)
{
	int	i;
	
	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && !ft_isspace(s[i + 1]))
			return (i + 1);
		i++;
	}
	return (-1);
}

int	is_good_variable(char *s)
{
	return (ft_isalpha(*s) || *s == '_');
}

int	get_key_length(char *s)
{
	int	i;

	i = 0;
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	return (i);
}

/*

insert value (c : un pointeur sur content de token de node) : 1 si erreur 0 sinon
	new content de expand = get value (c + i)
	si new content est null
		return 1
	new content = calloc dune chaine de taille strlen de c + len value (c + i ) - key length (c + i) -1 + 1
	strncpy dans new content de c jusqua i - 1 - 1 
	strcpy dans new content + i - 1 de get value (c + i)
	strcpy dans new content + i - 1 + get value length(c + i) de c + i + get key length (c + i)
	return 0

remove bad key(c : un pointeur sur content de token de node) : 1 si erreur 0 sinon
	new content = calloc dune chaine de taille strlen de c - 2 + 1
	si new content est null
		return 1
	strncpy dans new content de c jusqua i - 1 - 1
	strcpy dans new content + i - 1 de c + i + 1 
	return 0

expand_variables_token (c : un pointeur sur content de token de node) : 1 si erreur 0 sinon
remplace le content par un content dont les variables sont expanded
si apres le dollar on a une variable corrcte ie qui commence par un caractere alpha ou underscore suivi de alpha numerique ou underscore -> chercher la valeur de cette variable et la remplacer
si apres le dollar on a une variable incorrecte on retire tout ce qui est incorrect du content
si apres le dollar on a un white space on fait rien
	i = 0
	tant que (has interresting dollar (c + i)
		si is good variable (c + i) et insert value (c + i, pointeur sur i)
			return 1
		sinon si remove bad variable (c + i, pointeur sur i)
			return 1

*/



int	expand_variables_token(char **token)
{
	int	i;

	i = find_dollar(token);
	while (i != -1)
	{
		if (is_good_variable(token + i) && insert_value(&token, i))
			return (1);
		else if (remove_bad_variable(&token, i))
			return (1);
		i = find_dollar(token);
	}
}

int	expand_variables(t_list **tokens)
{
	t_current_token	current;

	init_current_token(&current, *tokens);
	while (current.node)
	{
		if ((current.type == TOKEN_FILE || current.type == TOKEN_COMMAND)
			&& expand_variables_token(&current.content))
			return (1);
		init_current_token(&current, current.node->next);
	}
	return (0);
}
