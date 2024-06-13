/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:41:33 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/13 13:37:51 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

/* init_ast.c */
void	init_ast(t_data *data);
t_list	*copy_tokens(t_list *tokens, int size, t_data *data);
t_tree	*tree_new(t_list *tokens, t_data *data);


#endif