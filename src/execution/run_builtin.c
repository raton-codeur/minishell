/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:26:32 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/17 16:57:38 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	run_builtin_in_parent(t_tree *tree, t_data *data)
{
	while (tree && get_broket(tree->content))
		tree = tree->right;
	if (tree == NULL)
		return (0);
	if (ft_strcmp(get_content(tree), "cd") == 0)
		return (cd_(tree, data, 1), 1);
	else if (ft_strcmp(get_content(tree), "export") == 0)
		return (export_(tree, data, 1), 1);
	else if (ft_strcmp(get_content(tree), "unset") == 0)
		return (unset_(tree, data, 1), 1);
	else if (ft_strcmp(get_content(tree), "exit") == 0)
		return (exit_(tree, data, 1), 1);
	else
		return (0);
}

void	run_builtin_in_child(t_tree *tree, t_data *data)
{
	if (ft_strcmp(get_content(tree), "echo") == 0)
		echo_(tree, data);
	if (ft_strcmp(get_content(tree), "cd") == 0)
		cd_(tree, data, 0);
	if (ft_strcmp(get_content(tree), "pwd") == 0)
		pwd_(data);
	if (ft_strcmp(get_content(tree), "export") == 0)
		export_(tree, data, 0);
	if (ft_strcmp(get_content(tree), "unset") == 0)
		unset_(tree, data, 0);
	if (ft_strcmp(get_content(tree), "env") == 0)
		env_(data);
	if (ft_strcmp(get_content(tree), "exit") == 0)
		exit_(tree, data, 0);
}

void	finish_builtin(int in_parent, int exit_status, t_data *data)
{
	if (!in_parent)
	{
		free_all(data);
		exit(exit_status);
	}
	else
		g_exit_status = exit_status;
}
