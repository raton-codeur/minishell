/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:38:17 by jteste            #+#    #+#             */
/*   Updated: 2024/06/25 14:12:22 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmm.h"

void	*mmm_malloc(size_t size)
{
	void	*memory;
	t_mmm	*new;
	t_mmm	**mmm;

	memory = malloc(size);
	if (!memory)
		return (NULL);
	mmm_bzero(memory, size);
	mmm = mmm_head();
	new = mmm_new(memory, false, 0);
	mmm_add_back(mmm, new);
	return (memory);
}

void	mmm_free(void *memory)
{
	t_mmm	*current;
	t_mmm	*back;
	t_mmm	**mmm;

	if (!memory)
		return ;
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
			free(memory);
			free(current);
			return ;
		}
		back = current;
		current = current->next;
	}
	free(memory);
}

int	mmm_open(char *pathname, int flags)
{
	int		fd;
	t_mmm	*new;
	t_mmm	**mmm;

	fd = open(pathname, flags);
	if (fd < 0)
		return (fd);
	mmm = mmm_head();
	new = mmm_new(0, true, fd);
	mmm_add_back(mmm, new);
	return (fd);
}

void	mmm_close(int fd)
{
	t_mmm	*current;
	t_mmm	*back;
	t_mmm	**mmm;

	if (fd < 0)
		return ;
	mmm = mmm_head();
	current = *mmm;
	back = 0;
	while (current)
	{
		if (current->fd == fd)
		{
			if (back != 0)
				back->next = current->next;
			else
				*mmm = current->next;
			close(fd);
			free(current);
			return ;
		}
		back = current;
		current = current->next;
	}
	close(fd);
}

void	mmm_free_all(void)
{
	t_mmm	*current;
	t_mmm	*tmp;
	t_mmm	**mmm;

	mmm = mmm_head();
	current = *mmm;
	if (!current)
		return ;
	while (current)
	{
		tmp = current;
		current = current->next;
		if (tmp->is_fd == true)
			close(tmp->fd);
		else
			free(tmp->memory);
		free(tmp);
	}
	*mmm = NULL;
}
