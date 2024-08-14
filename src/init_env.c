/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:52:30 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/12 17:05:32 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	proper_shlvl(char *s)
{
	if (s[0] == '\0')
		return (0);
	if (!ft_strisdigit(s))
		return (0);
	if (ft_strlen(skip_zeros(s)) >= 4)
		return (0);
	if (ft_atoi(skip_zeros(s)) >= 999)
		return (0);
	return (1);
}

static void	init_shlvl(t_data *data)
{
	t_list	*node;
	char	*new_value;

	node = in_env("SHLVL", data);
	if (node == NULL)
		insert_in_env("SHLVL=1", data);
	else
	{
		if (!proper_shlvl(get_value(node)))
			new_value = ft_strdup("1");
		else
			new_value = ft_itoa(ft_atoi(get_value(node)) + 1);
		if (new_value == NULL)
			return (error_exit(MALLOC, data));
		reset_value("SHLVL", new_value, data);
	}
}

static void	init_pwd(t_data *data)
{
	t_list	*node;
	char	*new_value;

	node = in_env("PWD", data);
	if (node == NULL)
		insert_in_env("PWD=", data);
	new_value = getcwd(NULL, 0);
	if (new_value == NULL)
		return (perror(NULL), error_exit(0, data));
	reset_value("PWD", new_value, data);
}

static void	minimum_env(t_data *data)
{
	init_shlvl(data);
	init_pwd(data);
	if (!in_env("OLDPWD", data))
		insert_in_env("OLDPWD", data);
	init_path(data);
}

void	init_env(t_data *data, char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return (minimum_env(data));
	while (envp[i])
		insert_in_env(envp[i++], data);
	minimum_env(data);
}
