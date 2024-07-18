/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:37:14 by jteste            #+#    #+#             */
/*   Updated: 2024/07/18 21:30:39 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*dup_home(t_data *data)
{
	char	*result;

	result = get_value(in_env("HOME", data));
	if (result == NULL)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), NULL);
	result = ft_strdup(result);
	if (result == NULL)
		error_exit(MALLOC, data);
	return (result);
}
