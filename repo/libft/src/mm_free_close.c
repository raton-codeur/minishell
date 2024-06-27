/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_free_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:04:26 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/26 17:04:41 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_mm	*mm_find_p(void *p)
{
	t_mm	*current;
	t_mm	**mm;

	mm = get_mm();
	if (*mm == NULL || p == NULL)
		return (NULL);
	current = *mm;
	while (current)
	{
		if ((unsigned long)current->p == (unsigned long)p)
			return (current);
		current = current->next;
	}
	return (NULL);
}

static t_mm	*mm_find_fd(int fd)
{
	t_mm	*current;
	t_mm	**mm;

	mm = get_mm();
	if (*mm == NULL)
		return (NULL);
	current = *mm;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	mm_free(void *p)
{
	t_mm	*to_remove;

	to_remove = mm_find_p(p);
	if (to_remove == NULL)
		return ;
	mm_remove_node(to_remove);
}

void	mm_close(int fd)
{
	t_mm	*to_remove;

	to_remove = mm_find_fd(fd);
	if (to_remove == NULL)
		return ;
	mm_remove_node(to_remove);
}

void	mm_free_all(void)
{
	t_mm	**mm;
	t_mm	*current;
	t_mm	*next;

	mm = get_mm();
	if (*mm == NULL)
		return ;
	current = *mm;
	while (current)
	{
		next = current->next;
		mm_remove_node(current);
		current = next;
	}
	*mm = NULL;
}
