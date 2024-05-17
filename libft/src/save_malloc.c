/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:11:46 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/19 13:23:59 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	save_malloc(void *p, t_list **l, void (*ft_free)(void *content))
{
	t_list	*node;

	node = list_new(p);
	if (node == NULL)
		return (list_clear(l, ft_free), 1);
	list_add_back(l, node);
	return (0);
}
