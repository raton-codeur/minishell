/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:13:17 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/19 13:26:41 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_list(\
	size_t count, size_t size, t_list **l, void (*ft_free)(void *content))
{
	void	*result;

	result = ft_calloc(count, size);
	if (result == NULL)
		return (list_clear(l, ft_free), NULL);
	if (save_malloc(result, l, ft_free))
		return (list_clear(l, ft_free), NULL);
	return (result);
}
