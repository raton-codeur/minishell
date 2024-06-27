/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:47:08 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/26 17:19:46 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*list_new(void *content)
{
	t_list	*result;

	result = mm_calloc(1, sizeof(t_list));
	if (result)
	{
		result->content = content;
		result->next = NULL;
		result->previous = NULL;
	}
	return (result);
}
