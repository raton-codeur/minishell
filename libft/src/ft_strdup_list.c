/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:13:11 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/19 13:29:51 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_list(\
	const char *s, t_list **l, void (*ft_free)(void *content))
{
	char	*result;

	result = ft_strdup(s);
	if (result == NULL)
		return (list_clear(l, ft_free), NULL);
	if (save_malloc(result, l, ft_free))
		return (list_clear(l, ft_free), NULL);
	return (result);
}
