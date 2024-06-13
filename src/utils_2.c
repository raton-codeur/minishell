/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:17:51 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/13 10:18:10 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tree_clear(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left == NULL && tree->right == NULL)
	{
		list_clear((t_list **)&tree->content, free_token);
		free(tree);
		return ;
	}
	tree_clear(tree->left);
	tree_clear(tree->right);
	list_clear((t_list **)&tree->content, free_token);
	free(tree);
}
