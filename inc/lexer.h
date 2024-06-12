/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:07:40 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/12 16:50:37 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# define MALLOC_MSG "malloc error"
# define MALLOC 426

// dans le main
// a supp
void	print_type(int type);
void	print_token(void *p);

/* utils.c */
void	*save(void *p, t_data *data);
void	free_token(void *p);
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
void	remove_node_and_update(\
	t_data *data, t_iterable *current, t_iterable *next);

/* change_node.c */
void	change_type(t_data *data, int type, int new_type);
void	remove_by_type(t_data *data, int type);
void	remove_by_type_content(t_data *data, int type, char *content);
void	merge_type(t_data *data, int type);
void	change_double_type(\
	t_data *data, int type, char *new_content, int new_type);






#endif
