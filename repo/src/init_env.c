/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:52:30 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/08 16:52:20 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_good_SHLVL(char *s)
{
	if (s == NULL | s[0] == '\0')
		return (0);
	if (!ft_strisdigit(s))
		return (0);
	if (ft_strlen(skip_zeros(s)) >= 4)
		return (0);
	if (ft_atoi(skip_zeros(s)) >= 999)
		return (0);
	return (1);
}

static void	init_SHLVL(t_data *data)
{
	t_list	*node;
	char	*new_value;

	node = in_env("SHLVL", data);
	if (node == NULL)
		add_to_env("SHLVL=1", data);
	else
	{
		if (!is_good_SHLVL(get_value(node)))
			new_value = ft_strdup("1");
		else
			new_value = ft_itoa(ft_atoi(get_value(node)) + 1);
		if (new_value == NULL)
			return (error_exit(MALLOC, data));
		reset_value("SHLVL", new_value, data);
	}
}

static void	init_PWD(t_data *data)
{
	t_list	*node;
	char	*new_value;

	node = in_env("PWD", data);
	if (node == NULL)
		add_to_env("PWD=", data);
	new_value = getcwd(NULL, 0);
	if (new_value == NULL)
		return (perror(NULL), error_exit(0, data));
	reset_value("PWD", new_value, data);
}

static void	init_OLDPWD(t_data *data)
{
	t_list	*node;

	node = in_env("OLDPWD", data);
	if (node == NULL)
		add_to_env("OLDPWD=", data);
}

static void	minimum_env(t_data *data)
{
	init_SHLVL(data);
	init_PWD(data);
	init_OLDPWD(data);
}

void	init_env(t_data *data, char **envp)
{
	int		i;

	i = 0;
	if (envp == NULL)
		return (minimum_env(data));
	while (envp[i])
		add_to_env(envp[i++], data);
	minimum_env(data);
}
