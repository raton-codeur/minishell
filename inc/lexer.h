/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:07:40 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/04 21:31:14 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_token
{
	char	*content;
	int		type;
}	t_token;

typedef struct s_data
{
	t_list	*to_free;
	char	*input;
	t_list	*tokens;
	t_token	*t;
	char	*s;
}	t_data;

enum
{
	TYPE_PIPE,
	TYPE_BROKET_LEFT,
	TYPE_BROKET_RIGHT,
	TYPE_SIMPLE_QUOTE,
	TYPE_DOUBLE_QUOTE,
	TYPE_WHITE_SPACE,
	TYPE_CHARACTER,
	TYPE_ERROR,
	TYPE_WORD,
	TYPE_COMMAND,
	TYPE_FILE,
	TYPE_DELIMITER,
	TYPE_DOUBLE_BROKET_LEFT,
	TYPE_DOUBLE_BROKET_RIGHT,
};

// dans le main
// a supp
void	print_type(int type);
void	print_token(void *p);

/* utils.c */
void	*save(void *p, t_data *data);
void	free_node(void *node_address);
void	free_token(void *p);
void	free_save(void *p, t_data *data);
void	free_all(t_data *data);

/* get_tokens.c */
int		get_tokens(t_data *data);

/* lexing.c */
int		lexing(t_list **tokens);

/* broket_to_double_broket.c */
void	broket_to_double_broket(t_list **tokens);

/* analyze_brokets.c */
void	analyze_brokets(t_list **tokens);

/* split_file_tokens.c */
int		split_file_tokens(t_list **tokens);

/* check_syntax.c */
int		check_syntax(t_list *tokens);

/* expand_variables.c */
int		expand_variables(t_list **tokens);

/* remove_quotes.c */
int		remove_quotes(t_list **tokens);

#endif