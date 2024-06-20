/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:50:25 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/19 13:28:35 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	list_size(t_list *list)
{
	int	result;

	result = 0;
	while (list)
	{
		result++;
		list = list->next;
	}
	return (result);
}
