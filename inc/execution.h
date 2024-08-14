/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:40:30 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/12 16:31:11 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "ast.h"

/* execute.c */
void		execute(t_data *data);

/* get_heredocs.c */
void		get_heredocs(t_tree **tree, t_data *data);

/* run_cmd.c */
void		run_cmd(t_tree *tree, t_data *data);

/* execute_pipe.c */
void		execute_pipe(t_tree *tree, t_data *data);

/* set_redirections.h */
int			set_redirections(t_tree **tree, t_data *data);

/* prepare_execution.c */
void		prepare_execution_absolute(t_tree *tree, t_data *data);
void		prepare_execution_relative(t_tree *tree, t_data *data);

/* run_builtin.c */
int			run_builtin_in_parent(t_tree *tree, t_data *data);
void		run_builtin_in_child(t_tree *tree, t_data *data);
void		finish_builtin(int in_parent, int exit_status, t_data *data);

/* echo.c */
void		echo_(t_tree *tree, t_data *data);

/* cd.c */
void		cd_(t_tree *tree, t_data *data, int in_parent);

/* cd_utils.c */
char		*dup_home(t_data *data, char *arg);

/* pwd.c */
void		pwd_(t_data *data);

/* export.c */
void		export_(t_tree *tree, t_data *data, int in_parent);

/* export_print.c */
void		export_print(t_data *data);

/* unset.c */
void		unset_(t_tree *tree, t_data *data, int in_parent);

/* env.c */
void		env_(t_data *data);

/* exit.c */
void		exit_(t_tree *tree, t_data *data, int in_parent);

/* exit_utils.c */
int			is_long_long(char *n, t_data *data);
long long	ft_atoll(const char *s);

#endif