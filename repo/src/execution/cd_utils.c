/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:37:14 by jteste            #+#    #+#             */
/*   Updated: 2024/07/10 16:11:00 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*return_home(t_data *data)
{
	char	*result;

	result = get_value(in_env("HOME", data));
	if (result == NULL)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), NULL);
	result = ft_strdup(result);
	if (result == NULL)
		error_exit(MALLOC, data);
	return (result);
}

int	is_home_needed(char *arg, int argc)
{
	if ((argc == 1)
		|| (arg[0] == '~' && arg[1] == '\0')
		|| (arg[0] == '~' && arg[1] == '/'))
		return (1);
	else
		return (0);
}

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
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(new_path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (!S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(new_path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
		return (1);
	}
	if (access(new_path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(new_path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (1);
	}
	return (0);
}
