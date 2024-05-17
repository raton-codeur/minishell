/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:56:48 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/17 14:58:42 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	list_print(t_list *list, void (*ft_print)(void *content))
{
	while (list)
	{
		(*ft_print)(list->content);
		list = list->next;
	}
}
