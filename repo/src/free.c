/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:26:38 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/20 16:29:24 by qhauuy           ###   ########.fr       */
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
	clear_history();
}

void	reset_input(t_data *data)
{
	free_input(data);
	get_path(data);
}
