/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:59:19 by jteste            #+#    #+#             */
/*   Updated: 2024/06/25 15:03:42 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "exec.h"

/* pwd.c */
int	update_pwd(t_data *data);
int	pwd1(t_data *data);

/* env.c */
int	copy_env(t_data *data, const char **envp);

#endif