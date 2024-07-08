/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:40:30 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/08 17:07:43 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

/* set_redirections.h */
int			set_redirections(t_tree **tree, t_data *data);

/* get_heredocs.c */
void		get_heredocs(t_tree **tree, t_data *data);

/* prepare_exec.c */
void		prepare_exec_absolute(t_tree *tree, t_data *data);
void		prepare_exec_relative(t_tree *tree, t_data *data);

/* exec.c */
void		exec(t_data *data);

/* run_cmd.c */
void		run_cmd(t_tree *tree, t_data *data);

/* exec_pipe.c */
void		exec_pipe(t_tree *tree, t_data *data);

/* echo.c */
void		echo_(t_tree *tree, t_data *data);

/* cd.c */
int			cd_(t_tree *tree, t_data *data, int in_parent);

/* cd_utils.c */
int			check_symbolic_link(char *new_path);
int			check_cd_error(char *new_path);

/* pwd.c */
void	pwd_(t_data *data);

/* export.c */
int		export_(t_tree *tree, t_data *data, int in_parent);

/* export2.c */
void	export_error(t_list *new, t_data *data);
// t_envp		*creat_full_env_node(char *arg);
// t_envp		*creat_half_env_node(char *arg);
t_list		*copy_env_list(t_list **envp);

/* export_utils.c */
void		print_export_content(void *p);

/* unset.c */
int			unset_(t_tree *tree, t_data *data, int in_parent);

/* env.c */
void		env_(t_data *data);
char		**env_to_double_array(t_data *data);

/* exit.c */
int			exit_(t_tree *tree, t_data *data, int in_parent);

/* exit_utils.c */
int			is_long_long(char *n, t_data *data);
long long	ft_atoll(const char *s);

#endif