/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:12:59 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/18 16:44:40 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(void *p, t_list **l, void (*ft_free)(void *content))
{
	t_list	*node;

	node = *l;
	while (node)
	{
		if (node->content == p)
		{
			ft_free(node->content);
			node->content = NULL;
			return ;
		}
		node = node->next;
	}
}
