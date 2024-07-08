/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/08 23:01:41 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_data(&data, argc, argv, envp);
	while (1)
	{
		get_input(&data);
		parsing(&data);
		build_AST(&data);
		execute(&data);
		reset_input(&data);
	}
	return (free_all(&data), 0);
}
