/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:46:44 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/16 14:06:35 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	unset_(t_tree *tree, t_data *data, int in_parent)
{
	char	**argv;

	prepare_execution_relative(tree, data);
	argv = data->cmd->argv;
	argv++;
	while (*argv != NULL)
		remove_from_env(*argv++, data);
	finish_builtin(in_parent, 0, data);
}
