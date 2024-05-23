/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:07:40 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/23 18:49:14 by qhauuy           ###   ########.fr       */
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

typedef struct s_current_token
{
	t_list	*node;
	t_token	*token;
	char	*content;
	int		type;
}	t_current_token;	

// dans le main donc a supp
void	print_type(int type);
void	print_token(void *p);

/* get_tokens.c */
int		get_tokens(t_list **tokens, char *input);

/* lexing.c */
int		lexing(t_list **tokens);

/* lexing_utils.c */
void	free_token(void *p);
int		go_to_quote_end(char *input, t_get_tokens_utils *u);
void 	init_current_token(t_list **current_node_info, t_list *node);


/* broket_to_double_broket.c */
int		broket_to_double_broket(t_list **tokens);

/* analyze_brokets.c */
int		analyze_brokets(t_list **tokens);

/* split_file_tokens.c */
int		split_file_tokens(t_list **tokens);

/* check_syntax.c */
int		check_syntax(t_list *tokens);

/* expand_variables.c */
void	expand_variables(t_list **tokens);
int		has_interresting_dollar(char *s)


/* expand_variables_token.c */
int		expand_variables_token(char **token);

#endif