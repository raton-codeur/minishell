/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:14:22 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/03 17:05:26 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	exit_numeric_error(t_data *data)
{
	char	*message;
	char	*message_join;

	message = ft_strjoin("minishell: exit: ", data->cmd->argv[1]);
	if (!message)
		error_exit(MALLOC, data);
	message_join = ft_strjoin(message, ": numeric argument required");
	free(message);
	if (!message_join)
		error_exit(MALLOC, data);
	ft_putendl_fd(message_join, 2);
	free(message_join);
	free_all(data);
	exit(2);
}

static void	exit_with_code(t_data *data)
{
	unsigned char	exit_status;

	exit_status = ft_atoll(data->cmd->argv[1]);
	free_all(data);
	exit(exit_status);
}

void	exit_(t_tree *tree, t_data *data, int in_parent)
{
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
				exit_with_code(data);
		}
		else
			exit_numeric_error(data);
	}
	else
		return (free_all(data), exit(0));
}
