/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:25:09 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/25 13:25:40 by jteste           ###   ########.fr       */
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
		ft_free(node->content);
		mmm_free(node);
		return ;
	}
	current = *list;
	while (current->next != node)
		current = current->next;
	current->next = current->next->next;
	if (current->next)
		current->next->previous = current;
	ft_free(node->content);
	mmm_free(node);
}
