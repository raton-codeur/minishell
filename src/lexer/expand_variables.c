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
has interresting dollar (c : un content de token de node) : le res du test 
	while *c
		if *c == '$' && ft_isspace(*(c + 1))
			return 1 
		c++
	return 0

is good variable (c : un content de token de node a partir dune variable ) : le res du test
	si (c[0] n est pas un caractere alpha ou underscore) return 0
	sinon
		return 1

get_key_length (c : un content de token de node a partir dune variable correcte) : la longueur de la variable
	tant que (c[i] est un caractere alpha numerique ou underscore)
		i++
	return i

get value (c : un content de token de node a partir dune variable correcte ) : la valeur de la variable avec getenv
	faire get env de c
	si 

expand_variables_token (c : un pointeur sur content de token de node) : 1 si erreur 0 sinon
remplace le content par un content dont les variables sont expanded
si apres le dollar on a une variable corrcte ie qui commence par un caractere alpha ou underscore suivi de alpha numerique ou underscore -> chercher la valeur de cette variable et la remplacer
si apres le dollar on a une variable incorrecte on retire tout ce qui est incorrect du content
si apres le dollar on a un white space on fait rien
	i = 0
	tant que (has interresting dollar (c + i + 1)
		si is good variable (c + i)
			new content de expand = get value (c + i)
			si new content est null
				return 1
			new content = calloc dune chaine de taille strlen de c + len value (c + i ) - key length (c + i) -1 + 1
			strncpy dans new content de c jusqua i - 1 - 1 
			strcpy dans new content + i - 1 de get value (c + i)
			strcpy dans new content + i - 1 + get value length(c + i) de c + i + get key length (c + i)
		sinon
			new content = calloc dune chaine de taille strlen de c - 2 + 1
			si new content est null
				return 1
			strncpy dans new content de c jusqua i - 1 - 1
			strcpy dans new content + i - 1 de c + i + 1 

void	expand_variables(t_list **tokens) : 1 si erreur 0 sinon
	node = *tokens
	while (node)
		token = node->content
		content = token->content
		si ((token->type == FILE ou COMMAND) et (expand_variables_token(pointeur sur content))
			return 1
		node = node->next
	return 0
*/
