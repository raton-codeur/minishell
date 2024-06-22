/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:39:58 by jteste            #+#    #+#             */
/*   Updated: 2024/06/22 15:23:43 by qhauuy           ###   ########.fr       */
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
// 		free(data->oldpwd);
// 		data->oldpwd = data->pwd;
// 		free(data->pwd);
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
