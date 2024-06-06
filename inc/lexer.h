/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:07:40 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/06 17:46:22 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# define MALLOC_MSG "malloc error"
# define MALLOC 426

typedef struct s_token
{
	char	*content;
	int		type;
}	t_token;

enum
{
	T_PIPE,
	T_BROKET_LEFT,
	T_BROKET_RIGHT,
	T_SIMPLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_DOLLAR,
	T_WHITE_SPACE,
	T_CHARACTER,
	T_ERROR,
	T_VARIABLE,
	T_WORD,
	T_COMMAND,
	T_FILE,
	T_DELIMITER,
	T_DOUBLE_BROKET_LEFT,
	T_DOUBLE_BROKET_RIGHT,
};

typedef struct s_iterable
{
	t_list	*node;
	t_token	*token;
	char	*content;
	int		type;
}	t_iterable;

typedef struct s_data
{
	t_list		*to_free;
	char		*input;
	t_list		*tokens;
}	t_data;


// dans le main
// a supp
void	print_type(int type);
void	print_token(void *p);

/* utils.c */
void	*save(void *p, t_data *data);
void	free_node(void *node_address);
void	free_save(void *p, t_data *data);
void	free_all(t_data *data);
void	error_exit(int code, t_data *data);
void	change_type(t_data *data, int type, int new_type);

/* get_tokens.c */
void	get_tokens(t_data *data);

/* lexing.c */
int		lexing(t_data *data);

/* find_variables.c */
void	find_variables(t_data *data);

/* iterable.c */
void	set_iterable(t_iterable *i, t_list *node);
void	set_iterables(t_iterable *current, t_iterable *next, t_list *node);
void	remove_and_update_iterables(\
	t_data *data, t_iterable *current, t_iterable *next);

/* change_type.c */
void	change_type(t_data *data, int type, int new_type);
void	remove_type(t_data *data, int type);
void	merge_type(t_data *data, int type);
void	change_double_type(\
	t_data *data, int type, char *new_content, int new_type);







#endif