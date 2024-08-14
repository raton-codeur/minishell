/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:04:29 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/12 17:03:29 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc,
	(void)argv;
	ft_bzero(data, sizeof(t_data));
	data->out = 1;
	init_env(data, envp);
	set_parent_signals();
}

static char	*get_prompt(t_data *data)
{
	char	**prompt;
	char	*result;

	prompt = ft_calloc(3, sizeof(char *));
	if (prompt == NULL)
		error_exit(MALLOC, data);
	prompt[0] = getcwd(NULL, 0);
	prompt[1] = ft_strdup(" >>> ");
	if (prompt[0] && prompt[1] == 0)
		return (deep_free((void **)prompt, 3), error_exit(MALLOC, data), NULL);
	prompt[2] = ft_strjoin(prompt[0], prompt[1]);
	if (prompt[2] == NULL)
		return (deep_free((void **)prompt, 3), error_exit(MALLOC, data), NULL);
	result = ft_strdup(prompt[2]);
	deep_free((void **)prompt, 3);
	if (result == NULL)
		error_exit(MALLOC, data);
	return (result);
}

void	reset_input(t_data *data)
{
	char	*prompt;

	set_parent_signals();
	prompt = get_prompt(data);
	errno = 0;
	data->input = readline(prompt);
	free(prompt);
	if (data->input == NULL && errno)
		error_exit(READLINE, data);
	else if (data->input == NULL)
		return (printf("exit\n"), free_all(data), exit(g_exit_status));
	if (data->input && data->input[0] != '\0' && !ft_strisspace(data->input))
		add_history(data->input);
	get_path(data);
}
