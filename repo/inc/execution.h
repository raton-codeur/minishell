/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:40:30 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/13 14:12:52 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "ast.h"

/* get_heredocs.c */
void		get_heredocs(t_tree **tree, t_data *data);

/* set_redirections.h */
int			set_redirections(t_tree **tree, t_data *data);

/* prepare_exec.c */
void		prepare_exec_absolute(t_tree *tree, t_data *data);
void		prepare_exec_relative(t_tree *tree, t_data *data);

/* execute.c */
void		execute(t_data *data);
int			end_builtin(int in_parent, int exit_status, t_data *data);

/* run_cmd.c */
void		run_cmd(t_tree *tree, t_data *data);

/* exec_pipe.c */
void		exec_pipe(t_tree *tree, t_data *data);

/* echo.c */
void		echo_(t_tree *tree, t_data *data);

/* cd.c */
int			cd_(t_tree *tree, t_data *data, int in_parent);

/* cd_utils.c */
int			check_cd_error(char *new_path);
int			check_symbolic_link(char *new_path);
int			is_home_needed(char *arg, int argc);
char		*return_home(t_data *data);

/* pwd.c */
void		pwd_(t_data *data);

/* export.c */
int			export_(t_tree *tree, t_data *data, int in_parent);

/* unset.c */
int			unset_(t_tree *tree, t_data *data, int in_parent);

/* env.c */
void		env_(t_data *data);

/* exit.c */
int			exit_(t_tree *tree, t_data *data, int in_parent);

/* exit_utils.c */
int			is_long_long(char *n, t_data *data);
long long	ft_atoll(const char *s);

#endif