/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:26:24 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/16 16:30:27 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(int error, t_data *data)
{
	if (error == MALLOC)
		ft_putendl_fd("malloc error", 2);
	else if (error == READ_LINE)
		ft_putendl_fd("readline error", 2);
	else if (error == PIPE)
		ft_putendl_fd("pipe error", 2);
	else if (error == FORK)
		ft_putendl_fd("fork error", 2);
	free_all_error(data);
	exit(1);
}

void	reset_input_error(t_data *data)
{
	reset_input(data);
	tree_clear(&data->tree);
}

void	free_all_error(t_data *data)
{
	free_all(data);
	tree_clear(&data->tree);
}

void	syntax_error(char *token, t_data *data)
{
	char	*message;
	char	*to_free;

	message = ft_strjoin("syntax error near unexpected token `", token);
	if (!message)
		error_exit(MALLOC, data);
	to_free = message;
	message = ft_strjoin(message, "'");
	free(to_free);
	if (!message)
		error_exit(MALLOC, data);
	free(data->error.message);
	data->error.message = message;
	data->error.code = 2;
	ft_putendl_fd(data->error.message, 2);
	reset_input_error(data);
}
