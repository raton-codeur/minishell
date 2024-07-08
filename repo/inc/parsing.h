/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:59:24 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/08 22:59:29 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/* init_tokens.c */
void	init_tokens(t_data *data);

/* parsing.c */
void	parsing(t_data *data);

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
void	change_node(\
	t_list **node, char *new_content, int new_type, t_data *data);
void	change_double_type(\
	t_data *data, int type, char *new_content, int new_type);

#endif
