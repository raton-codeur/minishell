/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:09:53 by qhauuy            #+#    #+#             */
/*   Updated: 2024/05/21 16:19:59 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	t_list	*tokens;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			ft_putendl_fd("error", 2);
		else
		{
			if (input[0] != '\0' && !ft_strisspace(input))
				add_history(input);
			tokens = get_tokens(input);
			free(input);
			list_print(tokens, print_token);
		}
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
