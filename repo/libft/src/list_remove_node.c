/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:25:09 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/11 14:48:00 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	list_remove_node(\
	t_list **list, t_list *node, void (*ft_free)(void *node_content))
{
	t_list	*current;

	if (!list || !*list || !node || !ft_free)
		return ;
	if (*list == node)
	{
		*list = node->next;
		if (node->next)
			node->next->previous = NULL;
		ft_free(node->content);
		free(node);
		return ;
	}
	current = *list;
	while (current->next != node)
		current = current->next;
	current->next = current->next->next;
	if (current->next)
		current->next->previous = current;
	ft_free(node->content);
	free(node);
}
