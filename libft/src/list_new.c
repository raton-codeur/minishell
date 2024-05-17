/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:47:08 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/17 14:50:40 by qhauuy           ###   ########.fr       */
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
	}
	return (result);
}
