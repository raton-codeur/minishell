/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:58:55 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/25 13:25:16 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	list_clear(t_list **list, void (*ft_free)(void *content))
{
	t_list	*node;
	t_list	*next_node;

	if (list == NULL || *list == NULL)
		return ;
	node = *list;
	*list = NULL;
	while (node)
	{
		next_node = node->next;
		if (ft_free != NULL)
			(*ft_free)(node->content);
		mmm_free(node);
		node = next_node;
	}
}
