/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:47:08 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/25 13:10:21 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*list_new(void *content)
{
	t_list	*result;

	result = mmm_malloc(sizeof(t_list));
	if (result)
	{
		result->content = content;
		result->next = NULL;
		result->previous = NULL;
	}
	return (result);
}
