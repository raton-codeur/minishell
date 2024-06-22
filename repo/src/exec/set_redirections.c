/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:36:47 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/22 16:47:43 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	is_broket(t_tree **tree)
{
	return (get_type(*tree) == T_BROKET_LEFT
		|| get_type(*tree) == T_BROKET_RIGHT
		|| get_type(*tree) == T_DOUBLE_BROKET_RIGHT
		|| get_type(*tree) == T_DOUBLE_BROKET_LEFT);
}

static int	set_in(t_tree **tree, t_data *data)
{
	if (data->in != 0)
		close(data->in);
	data->in = open(get_content((*tree)->left), O_RDONLY);
	if (data->in == -1)
		return (fd_error(get_content((*tree)->left), data), 1);
	return (0);
}

static int	set_out(t_tree **tree, t_data *data)
{
	if (data->out != 1)
		close(data->out);
	data->out = open(\
		get_content((*tree)->left), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->out == -1)
		return (fd_error(get_content((*tree)->left), data), 1);
	return (0);
}

static int	set_append(t_tree **tree, t_data *data)
{
	if (data->out != 1)
		close(data->out);
	data->out = open(\
		get_content((*tree)->left), O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->out == -1)
		return (fd_error(get_content((*tree)->left), data), 1);
	return (0);
}

static void	set_here_doc(t_tree **tree, t_data *data)
{
	if (data->in != 0)
		close(data->in);
	data->in = get_here_doc((*tree)->right);
}

int	set_redirections(t_tree **tree, t_data *data)
{
	if (*tree == NULL || !is_broket(tree))
		return (0);
	if (get_type(*tree) == T_BROKET_LEFT
		&& set_in(tree, data))
		return (1);
	else if (get_type(*tree) == T_BROKET_RIGHT
		&& set_out(tree, data))
		return (1);
	else if (get_type(*tree) == T_DOUBLE_BROKET_RIGHT
		&& set_append(tree, data))
		return (1);
	else if (get_type(*tree) == T_DOUBLE_BROKET_LEFT)
		set_here_doc(tree, data);
	*tree = (*tree)->right;
	return (set_redirections(tree, data));
}
