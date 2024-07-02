/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:09 by jteste            #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/07/02 17:36:38 by jteste           ###   ########.fr       */
=======
/*   Updated: 2024/07/02 16:59:16 by qhauuy           ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// void	change_directory(char *path)
// {
// 	if (chdir(path) != 0)
// 		perror("cd");
// }

// char	*analyse_new_path(char *new_path, t_data *data)
// {
// 	char	*home;

<<<<<<< Updated upstream
	home = get_env("HOME", data->envp);
	if (home == NULL)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (NULL);
	}
	if ((data->cmd->argc == 1) || (new_path[0] == '~' && new_path[1] == '\0'))
		return (home);
	else if (new_path[0] == '~' && new_path[1] == '/')
	{
		new_path = ft_strjoin(home, new_path + 1);
		if (new_path == NULL)
			error_exit(MALLOC, data);
	}
	else
		new_path = data->cmd->argv[1];
	return (new_path);
}
=======
// 	home = get_env("HOME", data->envp);
// 	if (home == NULL)
// 	{
// 		ft_putendl_fd("cd: HOME not set", 2);
// 		return (NULL);
// 	}
// 	if ((new_path[0] == '~' && new_path[1] == '\0') || (data->cmd->argc == 1))
// 		return (home);
// 	else if (new_path[0] == '~' && new_path[1] == '/')
// 		new_path = ft_strjoin(home, new_path + 1);
// 	if (new_path == NULL)
// 		error_exit(MALLOC, data);
// 	else
// 		new_path = data->cmd->argv[1];
// 	return (new_path);
// }
>>>>>>> Stashed changes

// int	cd_(t_tree *tree, t_data *data, int in_parent)
// {
// 	char	*new_path;

<<<<<<< Updated upstream
	(void)in_parent;
	prepare_exec_relative(tree, data);
	if (data->cmd->argc > 2)
	{
		ft_putendl_fd("Minishell: cd: too many arguments", 2);
		return (1);
	}
	else
		new_path = analyse_new_path(data->cmd->argv[1], data);
	if (new_path == NULL)
		return (1);
	modify_key_value(&data->envp, "OLDPWD", get_env("PWD", data->envp));
	change_directory(new_path);
	modify_key_value(&data->envp, "PWD", getcwd(NULL, 0));
	return (0);
}
=======
// 	prepare_argv(tree, data);
// 	if (data->cmd->argc > 2)
// 	{
// 		ft_putendl_fd("cd: too many arguments", 2);
// 		return (1);
// 	}
// 	else
// 		new_path = analyse_new_path(data->cmd->argv[1], data);
// 	if (new_path == NULL)
// 		return (1);
// 	modify_key_value(&data->envp, "OLDPWD", get_env("PWD", data->envp));
// 	change_directory(new_path);
// 	modify_key_value(&data->envp, "PWD", getcwd(NULL, 0));
// 	return (0);
// }
>>>>>>> Stashed changes
