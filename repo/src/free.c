/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:26:38 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/22 23:03:18 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_input(t_data *data)
{
	free(data->input);
	data->input = NULL;
	list_clear(&data->tokens, free_token);
	tree_clear(&data->ast);
	tree_clear(&data->tree);
	deep_free((void **)data->path, get_length(data->path));
	data->path = NULL;
	if (data->in != 0)
		close(data->in);
	data->in = 0;
	if (data->out != 1)
		close(data->out);
	data->out = 1;
	free_cmd(data);
}

void	free_all(t_data *data)
{
	free_input(data);
	rl_clear_history();
}

void	reset_input(t_data *data)
{
	free_input(data);
	get_path(data);
}

void	close_2(int pipe_[2])
{
	close(pipe_[0]);
	close(pipe_[1]);
}
