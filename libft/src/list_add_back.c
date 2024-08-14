/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:02:23 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/21 14:50:10 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	list_add_back(t_list **list, t_list	*node)
{
	t_list	*tmp;

	if (list == NULL || node == NULL)
		return ;
	if (*list == NULL)
	{
		*list = node;
		return ;
	}
	tmp = list_last(*list);
	tmp->next = node;
	node->previous = tmp;
}
