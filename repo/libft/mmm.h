/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:37:35 by jteste            #+#    #+#             */
/*   Updated: 2024/06/25 13:57:42 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MMM_H
# define MMM_H

# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_mmm
{
	void			*memory;
	bool			is_fd;
	int				fd;
	struct s_mmm	*next;
}	t_mmm;

t_mmm	**mmm_head(void);
t_mmm	*mmm_new(void *memory, bool is_fd, int fd);
void	mmm_add_back(t_mmm **lst, t_mmm *new);
bool	mmm_in_lst(void *memory);
void	*mmm_malloc(size_t size);
void	mmm_free(void *memory);
int		mmm_open(char *pathname, int flags);
void	mmm_close(int fd);
void	mmm_free_all(void);
void	mmm_add_track(void *memory);
void	mmm_remove_track(void *memory);
void	mmm_bzero(void *s, size_t n);
t_mmm	*find_mmm(void *memory);
void	remove_mmm(t_mmm *current);

#endif