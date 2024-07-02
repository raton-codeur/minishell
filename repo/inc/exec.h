/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:55:38 by qhauuy            #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/07/02 17:02:58 by jteste           ###   ########.fr       */
=======
/*   Updated: 2024/07/02 18:21:15 by qhauuy           ###   ########.fr       */
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
<<<<<<< Updated upstream
void	exec(t_data *data);
void	exec_pipe(t_tree *tree, t_data *data, int in_parent);

/* cd.c */
void	change_directory(char *path);
char	*analyse_new_path(char *new_path, t_data *data);
int		cd_(t_tree *tree, t_data *data, int in_parent);





=======
void		exec(t_data *data);
void		exec_pipe(t_tree *tree, t_data *data, int in_parent);
>>>>>>> Stashed changes

/* pwd.c */
int			update_pwd(t_data *data);
int			pwd1(t_data *data);

/* env.c */
int			copy_env(t_data *data, char **envp);
void		print_env(t_list **envp);
char		*get_env(char *key, t_list *envp);
char		**env_double_array(t_list *envp, t_data *data);

/* env2.c */
t_list	*find_env_key(t_list **envp, char *key_to_find);
void	modify_key_value(t_list **envp, char *key_to_find, char *new_value);

/* export.c */
void		sort_export_list(t_list **envp);
void		print_export(t_list **envp);

/* exit.c */
void		exit_(t_tree *tree, t_data *data, int in_parent);

/* exit_utils.c */
int			is_long_long(char *n, t_data *data);
long long	ft_atoll(const char *s);

/* exec_builtin.c */
int			exec_builtin(t_tree *tree, t_data *data, int in_parent);

#endif