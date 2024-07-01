/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:55:38 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/01 18:18:10 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "parser.h"
#include "builtins.h"

/* analyse_cmd.c */
void	analyse_cmd(t_tree *tree, t_data *data);
void	prepare_exec_relative(t_tree *tree, t_data *data);

/* set_redirections.h */
int	set_redirections(t_tree **tree, t_data *data);

/* get_heredocs.c */
void	get_heredocs(t_tree **tree, t_data *data);

/* exec.c */
void	exec(t_tree *tree, t_data *data);
void	exec_pipe(t_tree *tree, t_data *data);

#endif