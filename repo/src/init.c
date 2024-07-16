/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:04:29 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/16 13:53:37 by qhauuy           ###   ########.fr       */
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
	// signal(SIGQUIT, sigquit_handler);
}

static char	*get_prompt(t_data *data)
{
	char	**prompt;
	char	*result;

	prompt = ft_calloc(10, sizeof(char *));
	if (prompt == NULL)
		error_exit(MALLOC, data);
	prompt[0] = ft_strdup("[");
	prompt[1] = ft_itoa(g_exit_status);
	prompt[2] = ft_strdup("] ");
	prompt[3] = getcwd(NULL, 0);
	prompt[4] = ft_strdup(" >>> ");
	if (prompt[0] && prompt[1] && prompt[2] && prompt[3] && prompt[4] == 0)
		return (deep_free((void **)prompt, 10), error_exit(MALLOC, data), NULL);
	prompt[5] = ft_strjoin(prompt[0], prompt[1]);
	prompt[6] = ft_strjoin(prompt[5], prompt[2]);
	prompt[7] = ft_strjoin(prompt[6], prompt[3]);
	prompt[8] = ft_strjoin(prompt[7], prompt[4]);
	if (prompt[8] == NULL)
		return (deep_free((void **)prompt, 10), error_exit(MALLOC, data), NULL);
	result = ft_strdup(prompt[8]);
	deep_free((void **)prompt, 10);
	if (result == NULL)
		error_exit(MALLOC, data);
	return (result);
}

void	reset_input(t_data *data)
{
	char	*prompt;

	prompt = get_prompt(data);
	errno = 0;
	data->input = readline(prompt);
	free(prompt);
	if (data->input == NULL && errno)
		error_exit(READLINE, data);
	else if (data->input == NULL)
		return (free_all(data), exit(g_exit_status));
	if (data->input && data->input[0] != '\0' && !ft_strisspace(data->input))
		add_history(data->input);
	get_path(data);
	// signal(SIGINT, sigint_handler_parent);
}
