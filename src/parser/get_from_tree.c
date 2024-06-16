/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_from_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:23:40 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/16 22:23:55 by qhauuy           ###   ########.fr       */
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
