/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:41:33 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/16 22:23:52 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

/* init_ast.c */
void	init_ast(t_data *data);
t_list	*copy_tokens(t_list *tokens, int size, t_data *data);
t_tree	*tree_new(t_list *tokens, t_data *data);

/* build_tree.c */
void	build_tree(t_tree **tree, t_data *data);

/* build_tree_utils.c */
t_list	*find_pipe(t_list *tokens);
t_list	*find_brokets(t_list *tokens);
void	new_tree(t_data *data);

/* get_from_tree.c */
char	*get_content(t_tree *tree);
int		get_type(t_tree *tree);

#endif