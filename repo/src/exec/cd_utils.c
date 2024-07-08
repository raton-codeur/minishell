/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:14 by jteste            #+#    #+#             */
/*   Updated: 2024/07/08 14:03:28 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "exec.h"

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

int	is_in_parent(int in_parent, int exit_nb, t_data *data)
{
	if (!in_parent)
	{
		free_all(data);
		exit(exit_nb);
		return (exit_nb);
	}
	else
	{
		data->exit_status = exit_nb;
		return (exit_nb);
	}
}