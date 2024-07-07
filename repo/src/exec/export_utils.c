/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:13:54 by jteste            #+#    #+#             */
/*   Updated: 2024/07/06 13:24:34 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// void	print_export_content(void *p)
// {
// 	t_envp	*envp;
// 	char	*buff;
// 	char	*join;

// 	envp = p;
// 	buff = ft_strjoin("declare -x ", envp->key);
// 	if (buff == NULL)
// 		return ;
// 	join = ft_strjoin(buff, "=\"");
// 	if (join == NULL)
// 	{
// 		free(buff);
// 		return ;
// 	}
// 	free(buff);
// 	buff = ft_strjoin(join, envp->value);
// 	if (buff == NULL)
// 	{
// 		free(join);
// 		return ;
// 	}
// 	free(join);
// 	printf("%s\"\n", buff);
// 	free(buff);
// }
