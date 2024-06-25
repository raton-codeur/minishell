/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:55:38 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/25 15:04:59 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"
# include "builtins.h"

/* get_cmd.c */
void	get_cmd(t_tree *tree, t_data *data);

/* set_redirections.h */
int		set_redirections(t_tree **tree, t_data *data);

/* get_heredocs.c */
void	get_heredocs(t_tree **tree, t_data *data);

/* exec.c */
void	exec(t_tree *tree, t_data *data);
void	exec_child(t_tree *tree, t_data *data);

#endif