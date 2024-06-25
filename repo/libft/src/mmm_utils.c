/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:38:14 by jteste            #+#    #+#             */
/*   Updated: 2024/06/22 15:20:20 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmm.h"

t_mmm	**mmm_head(void)
{
	static t_mmm	*head;
	static int		i;

	if (i < 1)
	{
		head = NULL;
		i++;
	}
	return (&head);
}

t_mmm	*mmm_new(void *memory, bool is_fd, int fd)
{
	t_mmm			*new;

	new = malloc(sizeof(t_mmm));
	if (!new)
		return (NULL);
	new->memory = memory;
	new->is_fd = is_fd;
	new->fd = fd;
	new->next = NULL;
	return (new);
}

void	mmm_add_back(t_mmm **lst, t_mmm *new)
{
	t_mmm	*current;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

bool	mmm_in_lst(void *memory)
{
	t_mmm	*current;
	t_mmm	*back;
	t_mmm	**mmm;

	if (!memory)
		return (0);
	mmm = mmm_head();
	current = *mmm;
	back = 0;
	while (current)
	{
		if ((unsigned long)current->memory == (unsigned long)memory)
		{
			if (back != 0)
				back->next = current->next;
			else
				*mmm = current->next;
			return (1);
		}
		back = current;
		current = current->next;
	}
	return (0);
}

void	mmm_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}
