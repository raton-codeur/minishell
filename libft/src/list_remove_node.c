/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:25:09 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/23 15:34:58 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	list_remove_node(\
	t_list **list, t_list *node, void (*ft_free)(void *node))
{
	t_list	*current;
	t_list	*tmp;

	if (*list == node)
	{
		*list = node->next;
		(*list)->previous = NULL;
		ft_free(node);
	}
	current = *list;
	while (current->next != node)
		current = current->next;
	tmp = current->next;
	current->next = current->next->next;
	if (current->next)
		current->next->previous = current;
	ft_free(tmp);
}
