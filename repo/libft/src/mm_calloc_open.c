/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_calloc_open.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:04:51 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/26 17:05:05 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*mm_calloc(size_t count, size_t size)
{
	void	*result;
	t_mm	*new;

	result = ft_calloc(count, size);
	if (result == NULL)
		return (NULL);
	new = mm_new_node(result, 0);
	if (new == NULL)
		return (free(result), NULL);
	mm_add_node(new);
	return (result);
}

int	mm_open(char *pathname, int flags)
{
	int		result;
	t_mm	*new;

	result = open(pathname, flags);
	if (result < 0)
		return (result);
	new = mm_new_node(NULL, result);
	if (new == NULL)
		return (close(result), -1);
	mm_add_node(new);
	return (result);
}
