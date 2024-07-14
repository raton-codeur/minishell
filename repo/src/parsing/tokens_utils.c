/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:54:05 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/14 15:42:23 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	set_token(t_iterable current, char *content, int type)
{
	free(current.content);
	current.token->content = content;
	current.token->type = type;
}

int	get_broket(t_list *node)
{
	t_token	*token;

	if (node == NULL)
		return (0);
	token = node->content;
	if (token->type == T_BROKET_LEFT)
		return (T_BROKET_LEFT);
	else if (token->type == T_BROKET_RIGHT)
		return (T_BROKET_RIGHT);
	else if (token->type == T_DOUBLE_BROKET_LEFT)
		return (T_DOUBLE_BROKET_LEFT);
	else if (token->type == T_DOUBLE_BROKET_RIGHT)
		return (T_DOUBLE_BROKET_RIGHT);
	else
		return (0);
}
