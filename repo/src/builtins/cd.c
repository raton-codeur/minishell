/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:09 by jteste            #+#    #+#             */
/*   Updated: 2024/07/02 15:43:43 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// void	change_directory(char *path)
// {
// 	if (chdir(path) != 0)
// 		perror("cd");
// }

int	cd_(t_tree *tree, t_data *data, int in_parent)
{
	char *new_path;
	prepare_argv(tree, data);
	if (data->argc > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	else if (data->argc == 1)
	{
		new_path = get_env("HOME", data->env);
		if (!new_path)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (1);
		}
	}
	else
		new_path = data->cmd->argv[1];
	if (chdir(new_path) != 0)
		perror("cd :");
	
}