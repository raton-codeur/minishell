/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:09 by jteste            #+#    #+#             */
/*   Updated: 2024/07/08 14:03:31 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	change_directory(char *path, t_data *data)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
		perror("cd");
	modify_key_value(&data->envp, "OLDPWD", oldpwd);
	free(oldpwd);
	pwd = getcwd(NULL, 0);
	modify_key_value(&data->envp, "PWD", pwd);
	free(pwd);
}

static char	*analyse_new_path(char *new_path, t_data *data)
{
	char	*home;

	home = get_env("HOME", data->envp);
	if (home == NULL)
		ft_putendl_fd("cd: HOME not set", 2);
	if ((data->cmd->argc == 1) || (new_path[0] == '~' && new_path[1] == '\0'))
	{
		if (home == NULL)
			ft_putendl_fd("cd: HOME not set", 2);
		return (home);
	}
	else if (new_path[0] == '~' && new_path[1] == '/')
	{
		if (home == NULL)
			ft_putendl_fd("cd: HOME not set", 2);
		new_path = ft_strjoin(home, new_path + 1);
		if (new_path == NULL)
			error_exit(MALLOC, data);
	}
	else
		new_path = data->cmd->argv[1];
	return (new_path);
}

int	cd_(t_tree *tree, t_data *data, int in_parent)
{
	char	*new_path;

	prepare_exec_relative(tree, data);
	if (data->cmd->argc > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (is_in_parent(in_parent, 1, data));
	}
	new_path = analyse_new_path(data->cmd->argv[1], data);
	if (new_path == NULL)
		return (is_in_parent(in_parent, 1, data));
	if (check_cd_error(new_path) == 1)
		return (is_in_parent(in_parent, 1, data));
	if (check_symbolic_link(new_path) == 1)
	{
		ft_putendl_fd("cd: symbolic link not allowed", 2);
		return (is_in_parent(in_parent, 1, data));
	}
	change_directory(new_path, data);
	return (is_in_parent(in_parent, 0, data));
}