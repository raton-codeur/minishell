/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_position.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:23:22 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/13 12:24:17 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	node_position(t_list *list, t_list *node)
{
	int	result;

	result = 0;
	while (list && list != node)
	{
		result++;
		list = list->next;
	}
	return (result);
}
