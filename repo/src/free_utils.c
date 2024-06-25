/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:27:35 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/25 13:33:51 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *p)
{
	t_token	*token;

	token = p;
	mmm_free(token->content);
	if (token->here_doc != 0)
		close(token->here_doc);
	mmm_free(token);
}

void	tree_clear(t_tree **tree)
{
	if (*tree == NULL)
		return ;
	tree_clear(&(*tree)->left);
	tree_clear(&(*tree)->right);
	list_clear((t_list **)&(*tree)->content, free_token);
	mmm_free(*tree);
	*tree = NULL;
}

void	free_cmd(t_data *data)
{
	if (data->cmd)
	{
		mmm_free(data->cmd->pathname);
		mmm_free(data->cmd->argv);
		mmm_free(data->cmd);
		data->cmd = NULL;
	}
}
