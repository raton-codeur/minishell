/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:04:00 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/26 17:04:14 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_mm	**get_mm(void)
{
	static t_mm	*mm;

	return (&mm);
}

t_mm	*mm_new_node(void *p, int fd)
{
	t_mm	*new;

	new = malloc(sizeof(t_mm));
	if (new == NULL)
		return (NULL);
	new->p = p;
	new->fd = fd;
	new->next = NULL;
	return (new);
}

void	mm_add_node(t_mm *new)
{
	t_mm	**mm;
	t_mm	*current;

	mm = get_mm();
	if (*mm == NULL)
	{
		*mm = new;
		return ;
	}
	current = *mm;
	while (current->next)
		current = current->next;
	current->next = new;
}

static void	mm_free_node(t_mm *to_free)
{
	if (to_free->fd)
		close(to_free->fd);
	else
		free(to_free->p);
	free(to_free);
}

void	mm_remove_node(t_mm *to_remove)
{
	t_mm	**mm;
	t_mm	*current;

	mm = get_mm();
	if (*mm == NULL || to_remove == NULL)
		return ;
	if (*mm == to_remove)
	{
		*mm = to_remove->next;
		mm_free_node(to_remove);
		return ;
	}
	current = *mm;
	while (current->next != to_remove)
		current = current->next;
	current->next = current->next->next;
	mm_free_node(to_remove);
}
