/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:59:19 by jteste            #+#    #+#             */
/*   Updated: 2024/07/01 22:25:00 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "exec.h"
# include "libft.h"

/* pwd.c */
int	update_pwd(t_data *data);
int	pwd1(t_data *data);

/* env.c */
int		copy_env(t_data *data, char **envp);
void	print_env(t_list **envp);
char	*get_env(char *key, t_list *envp);
char	**env_double_array(t_list *envp, t_data *data);

/* export.c */
void	sort_export_list(t_list **envp);
void	print_export(t_list **envp);

/* exit.c */
void	exit_(t_tree *tree, t_data *data, int in_parent);

#endif