/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:49 by jteste            #+#    #+#             */
/*   Updated: 2024/07/02 15:33:59 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	find_builtin(t_tree *tree, t_data *data, int in_parent)
{
	// if (ft_strcmp(get_content(tree), "echo") == 0)
	// 	{
	// 		echo_(tree, data, in_parent);
	// 		return (1);
	// 	}
	// if (ft_strcmp(get_content(tree), "cd") == 0)
	// 	{
	// 		cd_(tree, data, in_parent);
	// 		return (1);
	// 	}
	// if (ft_strcmp(get_content(tree), "pwd") == 0)
	// 	{
	// 		pwd_(tree, data, in_parent);
	// 		return (1);
	// 	}
	// if (ft_strcmp(get_content(tree), "export") == 0)
	// 	{
	// 		export_(tree, data, in_parent);
	// 		return (1);
	// 	}
	// if (ft_strcmp(get_content(tree), "unset") == 0)
	// 	{
	// 		unset_(tree, data, in_parent);
	// 		return (1);
	// 	}
	// if (ft_strcmp(get_content(tree), "env") == 0)
	// 	{
	// 		env_(tree, data, in_parent);
	// 		return (1);
	// 	}
	if (ft_strcmp(get_content(tree), "exit") == 0)
		{
			exit_(tree, data, in_parent);
			return (1);
		}
	return (0);
}
