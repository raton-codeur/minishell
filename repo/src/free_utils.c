/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:27:35 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/26 18:11:13 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *p)
{
	t_token	*token;

	token = p;
	mm_free(token->content);
	if (token->here_doc != 0)
		close(token->here_doc);
	mm_free(token);
}

void	tree_clear(t_tree **tree)
{
	if (*tree == NULL)
		return ;
	tree_clear(&(*tree)->left);
	tree_clear(&(*tree)->right);
	list_clear((t_list **)&(*tree)->content, free_token);
	mm_free(*tree);
	*tree = NULL;
}

void	free_cmd(t_data *data)
{
	if (data->cmd)
	{
		mm_free(data->cmd->pathname);
		mm_free(data->cmd->argv);
		mm_free(data->cmd);
		data->cmd = NULL;
	}
}
