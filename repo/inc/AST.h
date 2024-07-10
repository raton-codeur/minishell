/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:41:33 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/10 12:10:43 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "parsing.h"

/* build_AST.c */
t_list	*copy_tokens(t_list *tokens, int size, t_data *data);
t_tree	*tree_new(t_list *tokens, t_data *data);
void	build_AST(t_data *data);

/* expand_tree.c */
void	expand_tree(t_tree **tree, t_data *data);

/* expand_tree_utils.c */
t_list	*find_pipe(t_list *tokens);
t_list	*find_brokets(t_list *tokens);
void	new_tree(t_data *data);

/* get_from_tree.c */
char	*get_content(t_tree *tree);
int		get_type(t_tree *tree);
int		get_here_doc(t_tree *tree);
int		is_broket(t_tree *tree);

#endif