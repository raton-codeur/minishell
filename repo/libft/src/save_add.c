/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:49:45 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/25 13:26:15 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	save_add(void *p, t_list **l)
{
	t_list	*node;

	node = list_new(p);
	if (node == NULL)
		return (list_clear(l, mmm_free), 1);
	list_add_back(l, node);
	return (0);
}
