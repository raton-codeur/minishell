/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:14:22 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/13 14:13:28 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	exit_numerical_error(t_data *data)
{
	char	*message;
	char	*message_join;

	message = ft_strjoin("minishell: exit: ", data->cmd->argv[1]);
	if (!message)
		error_exit(MALLOC, data);
	message_join = ft_strjoin(message, ": numeric argument required\n");
	free(message);
	if (!message_join)
		error_exit(MALLOC, data);
	ft_putstr_fd(message_join, 2);
	free(message_join);
	free_all(data);
	exit(2);
}

void	exit_(t_tree *tree, t_data *data, int in_parent)
{
	if (in_parent)
		ft_putstr_fd("exit\n", 2);
	prepare_execution_relative(tree, data);
	if (data->cmd->argc > 1)
	{
		if (is_long_long(data->cmd->argv[1], data))
		{
			if (data->cmd->argc > 2)
			{
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
				g_exit_status = 1;
				return (finish_builtin(in_parent, 1, data));
			}
			else
				finish_builtin(0, ft_atoll(data->cmd->argv[1]), data);
		}
		else
			return (exit_numerical_error(data));
	}
	else
		finish_builtin(0, g_exit_status, data);
}
