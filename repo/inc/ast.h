/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:41:33 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/13 22:55:30 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "parsing.h"

/* build_ast.c */
void	expand_tree(t_tree **tree, t_data *data);
void	build_ast(t_data *data);

/* build_ast_utils.c */
t_list	*find_pipe(t_list **node, t_tree *tree);
t_list	*find_broket(t_list **node, t_tree *tree);
void	new_tree(t_data *data);
t_list	*get_tokens(t_list *tokens, int size, t_data *data);

/* get_from_tree.c */
char	*get_content(t_tree *tree);
int		get_type(t_tree *tree);
int		get_here_doc(t_tree *tree);

#endif