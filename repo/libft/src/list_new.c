/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:47:08 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/21 14:50:13 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*list_new(void *content)
{
	t_list	*result;

	result = malloc(sizeof(t_list));
	if (result)
	{
		result->content = content;
		result->next = NULL;
		result->previous = NULL;
	}
	return (result);
}
