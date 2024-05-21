/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:07:40 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/21 18:38:52 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

enum	e_token_type
{
	TOKEN_PIPE,
	TOKEN_CHEVRON_LEFT,
	TOKEN_CHEVRON_RIGHT,
	TOKEN_WHITE_SPACE,
	TOKEN_WORD,
	TOKEN_ERROR,
	TOKEN_COMMAND,
	TOKEN_FILE,
	TOKEN_DELIMITER,
	TOKEN_DOUBLE_CHEVRON_LEFT,
	TOKEN_DOUBLE_CHEVRON_RIGHT,
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