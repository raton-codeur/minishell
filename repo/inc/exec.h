/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:40:30 by qhauuy            #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/07/04 17:21:10 by jteste           ###   ########.fr       */
=======
/*   Updated: 2024/07/04 18:31:48 by qhauuy           ###   ########.fr       */
>>>>>>> Stashed changes
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

/* exec_cmd.c */
void		exec_cmd(t_tree *tree, t_data *data, int in_parent);

/* exec.c */
void		exec(t_data *data);
void		exec_pipe(t_tree *tree, t_data *data, int in_parent);

/* cd.c */
int			cd_(t_tree *tree, t_data *data, int in_parent);

/* pwd.c */
int			pwd_(t_data *data, int in_parent);

/* env.c */
void		env_(t_data *data, t_list **envp, int in_parent);
int			copy_env(t_data *data, char **envp);
char		*get_env(char *key, t_list *envp);
char		**env_double_array(t_list *envp, t_data *data);

/* env2.c */
t_list		*find_env_key(t_list **envp, char *key_to_find);
void		modify_key_value(t_list **envp, char *key_to_find, char *new_value);

/* export.c */
void		export_(t_tree *tree, t_data *data, int in_parent);

/* export2.c */
void		export_error(char **key, char **value);
t_envp		*creat_full_env_node(char *arg);
t_envp		*creat_half_env_node(char *arg);
t_list		*copy_env_list(t_list **envp);

/* export_utils.c */
void	print_export_content(void *p);

/* exit.c */
void		exit_(t_tree *tree, t_data *data, int in_parent);

/* exit_utils.c */
int			is_long_long(char *n, t_data *data);
long long	ft_atoll(const char *s);

/* select_builtin.c */
int			has_builtin(t_tree *tree);
int			select_builtin(t_tree *tree, t_data *data, int in_parent);

#endif