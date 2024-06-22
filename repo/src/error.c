/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:26:24 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/20 17:39:21 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int code)
{
	if (code == MALLOC)
		ft_putendl_fd("memory allocation error", 2);
	else if (code == READ_LINE)
		ft_putendl_fd("readline failed", 2);
	else if (code == QUOTE)
		ft_putendl_fd("invalid quotes", 2);
}

void	error(int code, t_data *data)
{
	print_error(code);
	reset_input(data);
}

void	error_exit(int code, t_data *data)
{
	print_error(code);
	free_all(data);
	exit(1);
}

void	syntax_error(char *token, t_data *data)
{
	char	*message;
	char	*message_join;

	message = ft_strjoin("syntax error near unexpected token `", token);
	if (!message)
		error_exit(MALLOC, data);
	message_join = ft_strjoin(message, "'");
	free(message);
	if (!message_join)
		error_exit(MALLOC, data);
	ft_putendl_fd(message_join, 2);
	reset_input(data);
	/* mettre le code d'erreur de $? à 2 */
}

void	fd_error(char *file, t_data *data)
{
	perror(file);
	reset_input(data);
}
