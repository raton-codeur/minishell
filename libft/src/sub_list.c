/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:02:54 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/12 16:03:09 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*sub_list(t_list *lst, t_list *node, int list_size)
{
	int		i;
	t_list	*current;
	t_list	*sub_list;
	t_list	*tmp;

	i = 0;
	sub_list = NULL;
	current = lst;
	if (!lst || !node || list_size <= 0)
		return (NULL);
	while (current && current != node)
		current = current->next;
	if (!current)
		return (NULL);
	while (i < list_size && current)
	{
		tmp = list_new(current->content);
		if (!tmp)
		{
			list_clear(&sub_list, free);
			return (NULL);
		}
		list_add_back(&sub_list, tmp);
		current = current->next;
		i++;
	}
	return (sub_list);
}
