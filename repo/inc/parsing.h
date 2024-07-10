/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:59:24 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/10 15:30:34 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/* parsing.c */
void	parsing(t_data *data);

/* parsing_utils.c */
void	get_double_brokets(t_data *data);
void	get_words(t_data *data);
void	parse_brokets(t_data *data);

/* init_tokens.c */
void	init_tokens(t_data *data);

/* quotes.c */
void	parse_quotes(t_data *data);
void	remove_quotes(t_data *data);

/* parse_delimiters.c */
void	parse_delimiters(t_data *data);

/* expand_variables.c */
void	expand_variables(t_data *data);

/* iterate_on_tokens.c */
void	set_iterable(t_iterable *i, t_list *node);
void	set_iterables(t_iterable *current, t_iterable *next, t_list *node);
void	remove_and_update(t_data *data, t_iterable *current, t_iterable *next);

/* change_token.c */
void	change_type(t_data *data, int type, int new_type);
void	remove_by_type(t_data *data, int type);
void	remove_by_type_content(t_data *data, int type, char *content);
void	merge_type(t_data *data, int type);
void	change_node(\
	t_list **node, char *new_content, int new_type, t_data *data);
void	change_double_type(\
	t_data *data, int type, char *new_content, int new_type);

#endif
