/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_AST.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:19:45 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/11 23:39:55 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"

void	build_ast(t_data *data)
{
	if (data->tokens == NULL)
		return ;
	data->ast = ft_calloc(1, sizeof(t_tree));
	if (data->ast == NULL)
		error_exit(MALLOC, data);
	data->ast->content = copy_tokens(\
		data->tokens, list_size(data->tokens), data);
	expand_tree(&data->ast, data);
}
