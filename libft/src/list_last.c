/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_last.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:55:38 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/17 14:56:41 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*list_last(t_list *list)
{
	t_list	*node;

	if (list == NULL)
		return (NULL);
	node = list;
	while (node->next)
		node = node->next;
	return (node);
}
