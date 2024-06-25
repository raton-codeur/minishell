/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmm2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:38:19 by jteste            #+#    #+#             */
/*   Updated: 2024/06/25 13:57:04 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mmm.h"

void	mmm_add_track(void *memory)
{
	t_mmm	*new;
	t_mmm	**mmm;

	if (!memory)
		return ;
	if (mmm_in_lst(memory) == 1)
		return ;
	mmm = mmm_head();
	new = mmm_new(memory, false, 0);
	mmm_add_back(memory, new);
}

void	mmm_remove_track(void *memory)
{
	t_mmm	*current;
	t_mmm	*back;
	t_mmm	**mmm;

	if (!memory)
		return ;
	mmm = mmm_head();
	current = *mmm;
	back = 0;
	while (current != NULL)
	{
		if ((unsigned long)current->memory == (unsigned long)memory)
		{
			if (back != 0)
				back->next = current->next;
			else
				*mmm = current->next;
			free(current);
			return ;
		}
		back = current;
		current = current->next;
	}
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
