/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:41:33 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/13 16:09:00 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "parsing.h"

/* build_ast.c */
void	build_ast(t_data *data);

/* copy_tokens.c */
t_list	*copy_tokens(t_list *tokens, int size, t_data *data);

/* expand_tree.c */
void	expand_tree(t_tree **tree, t_data *data);

/* expand_tree_utils.c */
t_list	*find_pipe(t_list **node, t_tree *tree);
t_list	*find_broket(t_list **node, t_tree *tree);
void	new_tree(t_data *data);

/* get_from_tree.c */
char	*get_content(t_tree *tree);
int		get_type(t_tree *tree);
int		get_here_doc(t_tree *tree);
int		is_broket(t_tree *tree);

#endif