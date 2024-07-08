/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:14:22 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/08 22:56:02 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

static void	exit_with_code(char *code, t_data *data)
{
	unsigned char	exit_status;

	exit_status = ft_atoll(code);
	free_all(data);
	exit(exit_status);
}

int	exit_(t_tree *tree, t_data *data, int in_parent)
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
				return (end_builtin(in_parent, 1, data));
			}
			else
				return (exit_with_code(data->cmd->argv[1], data), 1);
		}
		else
			return (exit_numeric_error(data), 1);
	}
	else
		return (exit_with_code("0", data), 1);
}
