/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:12:57 by qhauuy            #+#    #+#             */
/*   Updated: 2024/06/13 10:21:33 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// t_list	*sub_tokens(t_list *tokens, t_list *node, int list_size)
// {
// 	int		i;
// 	t_list	*current;
// 	t_list	*result;
// 	t_list	*tmp;
// 	t_token	*content_copy;
// 	t_iterable	current;
// 	t_iterable	current_copy;

// 	i = 0;
// 	result = NULL;
// 	current = tokens;
// 	if (!tokens || !node || list_size <= 0)
// 		return (NULL);
// 	while (current && current != node)
// 		current = current->next;
// 	if (!current)
// 		return (NULL);
// 	while (i < list_size && current)
// 	{
// 		content_copy->content = ft_strdup(current->content->content);
// 		token->type = current->content->type;
// 		tmp = list_new(token);
// 		if (!tmp)
// 		{
// 			list_clear(&result, free);
// 			return (NULL);
// 		}
// 		list_add_back(&result, tmp);
// 		current = current->next;
// 		i++;
// 	}
// 	return (result);
// }

int	main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	while (1)
	{
		data.input = readline("minishell> ");
		if (data.input == NULL)
			ft_putendl_fd("readline error", 2);
		else
		{
			if (ft_strcmp(data.input, "exit") == 0)
				break ;
			if (data.input[0] != '\0' && !ft_strisspace(data.input))
				add_history(data.input);

			get_tokens(&data);
			if (lexing(&data))
				ft_putendl_fd("lexing error", 2);
			list_print(data.tokens, print_token);

			init_ast(&data);
			tree_print(data.ast);

			free(data.input);
			list_clear(&data.tokens, free_token);
			tree_clear(data.ast);
		}
	}
	return (free_all(&data), 0);
}
