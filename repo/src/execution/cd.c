/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:09 by jteste            #+#    #+#             */
/*   Updated: 2024/07/17 15:23:12 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	change_directory(char *path, t_data *data)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (free(path), error_exit(MALLOC, data));
	if (chdir(path) != 0)
		return (free(path), perror("cd"), free(oldpwd));
	free(path);
	path = NULL;
	reset_value("OLDPWD", oldpwd, data);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (error_exit(MALLOC, data));
	reset_value("PWD", pwd, data);
}

static char	*get_new_path(char *arg, t_data *data)
{
	char	*result;
	char	*tmp;

	if (is_home_needed(arg, data->cmd->argc) == 1)
	{
		result = return_home(data);
		if (result == NULL
			|| (data->cmd->argc == 1) || (arg[0] == '~' && arg[1] == '\0'))
			return (result);
		else
		{
			tmp = result;
			result = ft_strjoin(result, arg + 1);
			if (result == NULL)
				return (free(tmp), error_exit(MALLOC, data), NULL);
			return (free(tmp), result);
		}
	}
	else
	{
		result = ft_strdup(data->cmd->argv[1]);
		if (result == NULL)
			error_exit(MALLOC, data);
		return (result);
	}
}

void	cd_(t_tree *tree, t_data *data, int in_parent)
{
	char	*new_path;

	prepare_execution_relative(tree, data);
	if (data->cmd->argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (finish_builtin(in_parent, 1, data));
	}
	new_path = get_new_path(data->cmd->argv[1], data);
	if (new_path == NULL)
		return (finish_builtin(in_parent, 1, data));
	if (check_symbolic_link(new_path) == 1)
	{
		ft_putstr_fd("cd: symbolic link not allowed\n", 2);
		return (free(new_path), finish_builtin(in_parent, 1, data));
	}
	if (check_cd_error(new_path) == 1)
		return (free(new_path), finish_builtin(in_parent, 1, data));
	change_directory(new_path, data);
	finish_builtin(in_parent, 0, data);
}
