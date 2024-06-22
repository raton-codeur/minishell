/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:55:38 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/20 17:36:29 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "parser.h"

/* get_cmd.c */
void	get_cmd(t_tree *tree, t_data *data);

/* set_redirections.h */
int	set_redirections(t_tree **tree, t_data *data);

#endif
