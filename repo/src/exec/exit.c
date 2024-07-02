/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:14:22 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/02 18:35:39 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exit_(t_tree *tree, t_data *data, int in_parent)
{
	unsigned char	exit_status;

	if (in_parent)
		ft_putendl_fd("exit", 2);
	prepare_exec_relative(tree, data);
	if (data->cmd->argc > 1)
	{
		if (is_long_long(data->cmd->argv[1], data))
		{
			if (data->cmd->argc > 2)
			{
				ft_putendl_fd("minishell: exit: too many arguments", 2);
				data->exit_status = 1;
				if (!in_parent)
					return (free_all(data), exit(1));
			}
			else
			{
				exit_status = ft_atoll(data->cmd->argv[1]);
				return (free_all(data), exit(exit_status));
			}
		}
		else
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(data->cmd->argv[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			return (free_all(data), exit(2));
		}
	}
	else
		return (free_all(data), exit(0));
}
