/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:37:14 by jteste            #+#    #+#             */
/*   Updated: 2024/08/12 16:30:56 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*dup_home(t_data *data, char *arg)
{
	char	*result;

	result = get_value(in_env("HOME", data));
	if (result == NULL && arg == NULL)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), NULL);
	else if (result == NULL && arg[0] == '~')
	{
		result = ft_strdup("/home/qhauuy");
		return (result);
	}
	result = ft_strdup(result);
	if (result == NULL)
		error_exit(MALLOC, data);
	return (result);
}
