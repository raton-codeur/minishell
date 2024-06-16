/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:26:38 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/16 22:27:32 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *p)
{
	t_token	*token;

	token = p;
	free(token->content);
	free(token);
}

void	tree_clear(t_tree **tree)
{
	if (*tree == NULL)
		return ;
	tree_clear(&(*tree)->left);
	tree_clear(&(*tree)->right);
	list_clear((t_list **)&(*tree)->content, free_token);
	free(*tree);
	*tree = NULL;
}

void	reset_input(t_data *data)
{
	list_clear(&data->tokens, free_token);
	tree_clear(&data->ast);
	free(data->input);
	data->input = NULL;
	free(data->error.message);
	data->error.message = NULL;
	data->error.code = 0;
	get_path(data);
	if (data->in != 0)
		close(data->in);
	if (data->out != 1)
		close(data->out);
	data->in = 0;
	data->out = 1;
	if (data->cmd)
	{
		free(data->cmd->pathname);
		free(data->cmd->argv);
		free(data->cmd);
		data->cmd = NULL;
	}
}

void	free_all(t_data *data)
{
	reset_input(data);
	deep_free((void **)data->path, get_length(data->path));
	rl_clear_history();
}
