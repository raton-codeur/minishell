/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:59:24 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/13 17:03:20 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/* parse.c */
void	parse(t_data *data);

/* parsing_utils.c */
void	get_double_brokets(t_data *data);
void	find_last_dollar_chars(t_data *data);
void	get_words(t_data *data);
void	parse_brokets(t_data *data);

/* init_tokens.c */
void	init_tokens(t_data *data);

/* parse_quotes.c */
int		get_quote(t_iterable i);
void	get_char_in_quotes(t_data *data);
void	parse_quotes(t_data *data);

/* find_delimiters.c */
void	find_delimiters(t_data *data);

/* expand_variables.c */
void	expand_variables(t_data *data);

/* expand_variables_utils.c */
void	find_variables(t_data *data);
void	merge_variables(t_data *data);

/* tokens_utils.c */
void	set_token(t_iterable current, char *content, int type);
int		get_broket(t_list *node);

/* iterate_on_tokens.c */
void	set_iterable(t_iterable *i, t_list *node);
void	set_iterables(t_iterable *current, t_iterable *next, t_list *node);
void	remove_and_update(t_iterable *current, t_iterable *next, t_data *data);

/* change_tokens.c */
void	change_all_type(t_data *data, int type, int new_type);
void	remove_all_by_type(t_data *data, int type);
void	merge_type(t_data *data, int type);
void	change_all_consecutive(\
	t_data *data, int type, char *new_content, int new_type);

#endif