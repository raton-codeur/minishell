/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:02:23 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/17 17:03:12 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	list_add_back(t_list **list, t_list	*node)
{
	if (list)
	{
		if (*list)
			list_last(*list)->next = node;
		else
			*list = node;
	}
}
