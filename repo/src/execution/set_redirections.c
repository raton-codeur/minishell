/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:36:47 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/13 17:20:40 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	set_in(t_tree **tree, t_data *data)
{
	if (data->in != 0)
		close(data->in);
	data->in = open(get_content((*tree)->left), O_RDONLY);
	if (data->in == -1)
		return (fd_error(get_content((*tree)->left), data));
}

static void	set_out(t_tree **tree, t_data *data)
{
	if (data->out != 1)
		close(data->out);
	data->out = open(\
		get_content((*tree)->left), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->out == -1)
		return (fd_error(get_content((*tree)->left), data));
}

static void	set_append(t_tree **tree, t_data *data)
{
	if (data->out != 1)
		close(data->out);
	data->out = open(\
		get_content((*tree)->left), O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->out == -1)
		return (fd_error(get_content((*tree)->left), data));
}

static void	set_here_doc(t_tree **tree, t_data *data)
{
	if (data->in != 0)
		close(data->in);
	if ((*tree)->right == NULL)
		return ;
	data->in = get_here_doc(*tree);
}

int	set_redirections(t_tree **tree, t_data *data)
{
	int	broket;

	if (*tree == NULL)
		return (0);
	broket = get_broket((*tree)->content);
	if (broket == 0)
		return (0);
	if (broket == T_BROKET_LEFT)
		set_in(tree, data);
	else if (broket == T_BROKET_RIGHT)
		set_out(tree, data);
	else if (broket == T_DOUBLE_BROKET_RIGHT)
		set_append(tree, data);
	else if (broket == T_DOUBLE_BROKET_LEFT)
		set_here_doc(tree, data);
	*tree = (*tree)->right;
	return (set_redirections(tree, data));
}
