/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:07:40 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/23 13:20:25 by qhauuy           ###   ########.fr       */
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
	TOKEN_EOL,
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

// a supp
void	print_type(int type);
void	print_token(void *p);


/* get_tokens.c */
int		get_tokens(t_list **tokens, char *input);
void	free_token(void *p);

/* add_token.c */
int		add_token(t_list **tokens, char *input, t_get_tokens_utils *u);

/* lexing.c */
int		lexing(t_list **tokens);
int		list_remove(t_list **list, t_list *node);

/* broket_to_double_broket.c */
int		broket_to_double_broket(t_list **tokens);

/* analyze_brokets.c */
int		analyze_brokets(t_list **tokens);


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