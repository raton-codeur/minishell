/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:07:40 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/22 16:06:37 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

enum	e_token_type
{
	TOKEN_PIPE,
	TOKEN_BROKET_LEFT,
	TOKEN_BROKET_RIGHT,
	TOKEN_WHITE_SPACE,
	TOKEN_WORD,
	TOKEN_ERROR,
	TOKEN_COMMAND,
	TOKEN_FILE,
	TOKEN_DELIMITER,
	TOKEN_DOUBLE_BROKET_LEFT,
	TOKEN_DOUBLE_BROKET_RIGHT,
	TOKEN_QUOTE,
	TOKEN_DOUBLE_QUOTE
};

typedef struct s_token
{
	char	*content;
	int		type;
}	t_token;

typedef struct s_get_tokens_utils
{
	int		start;
	int		end;
	int		current_token_type;
}	t_get_tokens_utils;

/* get_tokens.c */
int		get_tokens(t_list **tokens, char *input);
void	free_token(void *p);

/* lexing.c */
int		lexing(t_list **tokens);
int		list_remove(t_list **list, t_list *node);

/* chevron_to_double_chevron.c */
int		chevron_to_double_chevron(t_list **tokens);

/*
etats pour parcourir un mot
base
simple quote
double quote

etats pour parcourir les tokens
chevron left
chevron right
double chevron left
double chevron right
*/

#endif