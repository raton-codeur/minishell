/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:40:30 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/07 18:34:21 by qhauuy           ###   ########.fr       */
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

/* pwd.c */
int			pwd_(t_data *data, int in_parent);

/* export.c */
// void		export_(t_tree *tree, t_data *data, int in_parent);

/* export2.c */
// void		export_error(char **key, char **value);
// t_envp		*creat_full_env_node(char *arg);
// t_envp		*creat_half_env_node(char *arg);
// t_list		*copy_env_list(t_list **envp);

/* export_utils.c */
// void		print_export_content(void *p);

/* unset.c */

/* env.c */
// void		env_(t_data *data, t_list **envp, int in_parent);
// int			copy_env(t_data *data, char **envp);
// char		*get_env(char *key, t_list *envp);
// char		**env_double_array(t_list *envp, t_data *data);

/* env2.c */
// t_list		*find_env_key(t_list **envp, char *key_to_find);
// void		modify_key_value(t_list **envp, char *key_to_find, char *new_value);

/* exit.c */
void		exit_(t_tree *tree, t_data *data, int in_parent);

/* exit_utils.c */
int			is_long_long(char *n, t_data *data);
long long	ft_atoll(const char *s);

#endif