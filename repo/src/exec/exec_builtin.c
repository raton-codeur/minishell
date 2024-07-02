/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:49 by jteste            #+#    #+#             */
/*   Updated: 2024/07/02 17:03:12 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_builtin(t_tree *tree, t_data *data, int in_parent)
{
	// if (ft_strcmp(get_content(tree), "echo") == 0)
	// 	return (echo_(tree, data, in_parent), 1);
	if (ft_strcmp(get_content(tree), "cd") == 0)
		return (cd_(tree, data, in_parent), 1);
	// if (ft_strcmp(get_content(tree), "pwd") == 0)
	// 	return (pwd_(tree, data, in_parent), 1);
	// if (ft_strcmp(get_content(tree), "export") == 0)
	// 	return (export_(tree, data, in_parent), 1);
	// if (ft_strcmp(get_content(tree), "unset") == 0)
	// 	return (unset_(tree, data, in_parent), 1);
	// if (ft_strcmp(get_content(tree), "env") == 0)
	// 	return (env_(tree, data, in_parent), 1);
	if (ft_strcmp(get_content(tree), "exit") == 0)
		return (exit_(tree, data, in_parent), 1);
	return (0);
}
