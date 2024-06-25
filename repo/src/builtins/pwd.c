/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:39:58 by jteste            #+#    #+#             */
/*   Updated: 2024/06/25 13:29:50 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// int	update_pwd(t_data *data)
// {
// 	char	*pwd;

// 	pwd = getcwd(NULL, 0);
// 	if (pwd == NULL)
// 		return (1);
// 	else
// 	{
// 		mmm_free(data->oldpwd);
// 		data->oldpwd = data->pwd;
// 		mmm_free(data->pwd);
// 		data->pwd = pwd;
// 		return (0);
// 	}
// }

// int	pwd1(t_data *data)
// {
// 	update_pwd(data);
// 	if (data->pwd == NULL)
// 		return (1);
// 	else
// 	{
// 		printf("%s\n", data->pwd);
// 		return (0);
// 	}
// }
