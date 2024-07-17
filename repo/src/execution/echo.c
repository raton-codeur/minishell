/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:50:21 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/17 16:49:37 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_option(char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	if (s[i] != '-')
		return (0);
	i++;
	if (s[i] != 'n')
		return (0);
	i++;
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

void	echo_(t_tree *tree, t_data *data)
{
	int		option;
	char	**argv;

	prepare_execution_relative(tree, data);
	argv = data->cmd->argv;
	argv++;
	option = 0;
	if (data->cmd->argc > 1)
	{
		option = is_option(*argv);
		while (is_option(*argv))
			argv++;
	}
	if (*argv)
		printf("%s", *argv++);
	while (*argv)
		printf(" %s", *argv++);
	if (!option)
		printf("\n");
	finish_builtin(0, 0, data);
}
