/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_from_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:23:40 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/05 15:26:13 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_content(t_tree *tree)
{
	t_list	*node;
	t_token	*token;

	node = tree->content;
	token = node->content;
	return (token->content);
}

int	get_type(t_tree *tree)
{
	t_list	*node;
	t_token	*token;

	node = tree->content;
	token = node->content;
	return (token->type);
}

int	get_here_doc(t_tree *tree)
{
	t_list	*node;
	t_token	*token;

	node = tree->content;
	token = node->content;
	return (token->here_doc);
}

int	is_broket(t_tree *tree)
{
	return (tree && (get_type(tree) == T_BROKET_LEFT
		|| get_type(tree) == T_BROKET_RIGHT
		|| get_type(tree) == T_DOUBLE_BROKET_RIGHT
		|| get_type(tree) == T_DOUBLE_BROKET_LEFT));
}
