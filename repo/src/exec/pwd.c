/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteste <jteste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:39:58 by jteste            #+#    #+#             */
/*   Updated: 2024/07/03 16:11:08 by jteste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	pwd_(int in_parent)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	if (!in_parent)
		exit(0);
	return (0);
}
