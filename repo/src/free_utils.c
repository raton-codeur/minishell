/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:27:35 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/27 12:22:26 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *p)
{
	t_token	*token;

	token = p;
	free(token->content);
	token->content = NULL;
	if (token->here_doc != 0)
		close(token->here_doc);
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

void	free_cmd(t_data *data)
{
	if (data->cmd)
	{
		free(data->cmd->pathname);
		free(data->cmd->argv);
		free(data->cmd);
		data->cmd = NULL;
	}
}

void	free_env(void *p)
{
	t_envp	*current;

	current = p;
	free(current->key);
	free(current->value);
	free(current);
}
