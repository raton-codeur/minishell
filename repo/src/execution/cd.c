/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:09 by jteste            #+#    #+#             */
/*   Updated: 2024/07/08 22:56:02 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	check_symbolic_link(char *new_path)
{
	struct stat	buf;

	if (lstat(new_path, &buf) == -1)
	{
		perror("lstat");
		return (1);
	}
	if (S_ISLNK(buf.st_mode) == 1)
		return (1);
	else
		return (0);
}

int	check_cd_error(char *new_path)
{
	struct stat	buf;

	if (stat(new_path, &buf) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(new_path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (!S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(new_path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
		return (1);
	}
	if (access(new_path, X_OK) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(new_path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (1);
	}
	return (0);
}

static void	change_directory(char *path, t_data *data)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (error_exit(MALLOC, data));
	if (chdir(path) != 0)
		return (perror("cd"), free(oldpwd));
	free(path);
	path = NULL;
	reset_value("OLDPWD", oldpwd, data);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (free(oldpwd), error_exit(MALLOC, data));
	reset_value("PWD", pwd, data);
}

static char	*analyse_new_path(char *new_path, t_data *data)
{
	char	*home;

	home = get_value(in_env("HOME", data));
	if (home == NULL)
		ft_putendl_fd("cd: HOME not set", 2);
	if ((data->cmd->argc == 1) || (new_path[0] == '~' && new_path[1] == '\0'))
	{
		if (home == NULL)
			ft_putendl_fd("cd: HOME not set", 2);
		home = ft_strdup(home);
		if (home == NULL)
			error_exit(MALLOC, data);
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
		return (end_builtin(in_parent, 1, data));
	}
	new_path = analyse_new_path(data->cmd->argv[1], data);
	if (new_path == NULL)
		return (end_builtin(in_parent, 1, data));
	if (check_cd_error(new_path) == 1)
		return (end_builtin(in_parent, 1, data));
	if (check_symbolic_link(new_path) == 1)
	{
		ft_putendl_fd("cd: symbolic link not allowed", 2);
		return (end_builtin(in_parent, 1, data));
	}
	change_directory(new_path, data);
	return (end_builtin(in_parent, 0, data));
}
