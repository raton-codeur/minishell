/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:41:33 by qhauuy            #+#    #+#             */
<<<<<<< HEAD:repo/inc/ast.h
/*   Updated: 2024/07/13 16:09:00 by qhauuy           ###   ########.fr       */
=======
/*   Updated: 2024/07/11 23:57:57 by qhauuy           ###   ########.fr       */
>>>>>>> 31260249afa83f1a2005fc9e3ad180e4a67731c3:repo/inc/AST.h
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "parsing.h"

<<<<<<< HEAD:repo/inc/ast.h
/* build_ast.c */
=======
/* build_AST.c */
>>>>>>> 31260249afa83f1a2005fc9e3ad180e4a67731c3:repo/inc/AST.h
void	build_ast(t_data *data);

/* copy_tokens.c */
t_list	*copy_tokens(t_list *tokens, int size, t_data *data);

/* expand_tree.c */
void	expand_tree(t_tree **tree, t_data *data);

/* expand_tree_utils.c */
<<<<<<< HEAD:repo/inc/ast.h
t_list	*find_pipe(t_list **node, t_tree *tree);
t_list	*find_broket(t_list **node, t_tree *tree);
void	new_tree(t_data *data);
=======
t_list	*find_pipe(t_list *tokens);
t_list	*find_brokets(t_list *tokens);
void	set_new_tree(t_data *data);
>>>>>>> 31260249afa83f1a2005fc9e3ad180e4a67731c3:repo/inc/AST.h

/* get_from_tree.c */
char	*get_content(t_tree *tree);
int		get_type(t_tree *tree);
int		get_here_doc(t_tree *tree);
int		is_broket(t_tree *tree);

#endif