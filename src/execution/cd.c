/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:09 by jteste            #+#    #+#             */
/*   Updated: 2024/08/13 15:12:38 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	*get_directory(char *arg, t_data *data)
{
	char	*result;
	char	*save;

	if (arg == NULL || arg[0] == '~')
	{
		result = dup_home(data, arg);
		if (result == NULL || arg == NULL || arg[1] == '\0')
			return (result);
		else
		{
			save = result;
			result = ft_strjoin(result, arg + 1);
			if (result == NULL)
				return (free(save), error_exit(MALLOC, data), NULL);
			return (free(save), result);
		}
	}
	else
	{
		result = ft_strdup(arg);
		if (result == NULL)
			error_exit(MALLOC, data);
		return (result);
	}
}

static int	symbolic_link(char *directory)
{
	struct stat	sb;

	if (lstat(directory, &sb) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(directory);
		return (1);
	}
	if (S_ISLNK(sb.st_mode))
	{
		ft_putstr_fd("minishell: cd: symbolic link not allowed\n", 2);
		return (1);
	}
	return (0);
}

static int	wrong_directory(char *directory)
{
	struct stat	sb;

	if (stat(directory, &sb) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(directory);
		return (1);
	}
	if (!S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(directory, 2);
		ft_putstr_fd(": Not a directory\n", 2);
		return (1);
	}
	if (access(directory, X_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(directory, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (1);
	}
	return (0);
}

static void	change_directory(char *directory, t_data *data)
{
	char	*pwd_dup;
	char	*new_pwd;

	if (chdir(directory))
		return (free(directory), perror("minishell: cd"));
	if (in_env("OLDPWD", data))
	{
		if (get_value(in_env("PWD", data)) == NULL)
			reset_value("OLDPWD", NULL, data);
		else
		{
			pwd_dup = ft_strdup(get_value(in_env("PWD", data)));
			if (pwd_dup == NULL)
				return (free(directory), error_exit(MALLOC, data));
			reset_value("OLDPWD", pwd_dup, data);
		}
	}
	if (in_env("PWD", data))
	{
		new_pwd = getcwd(NULL, 0);
		if (new_pwd == NULL)
			return (free(directory), perror(NULL), error_exit(0, data));
		reset_value("PWD", new_pwd, data);
	}
}

void	cd_(t_tree *tree, t_data *data, int in_parent)
{
	char	*directory;

	prepare_execution_relative(tree, data);
	if (data->cmd->argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (finish_builtin(in_parent, 1, data));
	}
	directory = get_directory(data->cmd->argv[1], data);
	if (directory == NULL)
		return (finish_builtin(in_parent, 1, data));
	else if (directory[0] == '\0')
		return (finish_builtin(in_parent, 0, data));
	if (wrong_directory(directory) || symbolic_link(directory))
		return (free(directory), finish_builtin(in_parent, 1, data));
	change_directory(directory, data);
	free(directory);
	finish_builtin(in_parent, 0, data);
}
