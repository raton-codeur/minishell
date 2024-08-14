/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:00:46 by jteste            #+#    #+#             */
/*   Updated: 2024/07/17 16:36:14 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	export_error(char *envp_line)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(envp_line, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_status = 1;
}

void	export_(t_tree *tree, t_data *data, int in_parent)
{
	int		i;
	char	*envp_line;

	g_exit_status = 0;
	prepare_execution_relative(tree, data);
	if (data->cmd->argc == 1)
		export_print(data);
	else
	{
		i = 1;
		while (i < data->cmd->argc)
		{
			envp_line = data->cmd->argv[i];
			if (is_proper(envp_line))
				insert_in_env(envp_line, data);
			else
				export_error(envp_line);
			i++;
		}
	}
	finish_builtin(in_parent, g_exit_status, data);
}
