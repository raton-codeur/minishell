/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:14:22 by qhauuy            #+#    #+#             */
/*   Updated: 2024/07/01 20:17:29 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"












static char	*skip_zero(char *s)
{
	int		i;
	char	*result;

	i = 0;
	result = s;
	while (s[i] == '0')
	{
		result++;
		i++;
	}
	if (s[i] == '\0')
		result--;
	return (result);
}

static int	string_is_greater(char *s, char *model)
{
	int	i;
	int	length_s;
	int	length_model;

	length_s = ft_strlen(s);
	length_model = ft_strlen(model);
	if (length_s > length_model)
		return (1);
	else if (length_s < length_model)
		return (0);
	else
	{
		i = 0;
		while (i < length_model)
		{
			if (s[i] > model[i])
				return (1);
			else if (s[i] < model[i])
				return (0);
			else
				i++;
		}
		return (0);
	}
}

int	ft_strisdigit(const char *s)
{
	while (ft_isspace(*s))
		s++;
	if (*s == '+' || *s == '-')
		s++;
	while (*s >= '0' && *s <= '9')
		s++;
	while (ft_isspace(*s))
		s++;
	return (*s == '\0');
}

void	trim_white_space(char **p)
{
	int		i;
	char	*s;

	s = *p;
	i = 0;
	while (!ft_isspace(s[i]))
		i++;
	(*p)[i] = '\0';
}

int	is_long_long(char *n)
{
	if (!ft_strisdigit(n))
		return (0);
	while (ft_isspace(*n))
		n++;
	trim_white_space(&n);
	if (*n == '+')
	{
		if (ft_strcmp(skip_zero(n + 1), "9223372036854775807") > 0)
			return (0);
	}
	else if (n[0] == '-')
	{
		if (ft_strcmp(skip_zero(n + 1), "9223372036854775808") > 0)
			return (1);
	}
	else if (string_is_greater(skip_zero(n), "9223372036854775807"))
		return (0);
	return (1);
}













// static char	*skip_zero(char *s)
// {
// 	int		i;
// 	char	*result;

// 	i = 0;
// 	result = s;
// 	while (s[i] == '0')
// 	{
// 		result++;
// 		i++;
// 	}
// 	if (s[i] == '\0')
// 		result--;
// 	return (result);
// }

// static int	string_is_greater(char *s, char *model)
// {
// 	int	i;
// 	int	length_s;
// 	int	length_model;

// 	length_s = ft_strlen(s);
// 	length_model = ft_strlen(model);
// 	if (length_s > length_model)
// 		return (1);
// 	else if (length_s < length_model)
// 		return (0);
// 	else
// 	{
// 		i = 0;
// 		while (i < length_model)
// 		{
// 			if (s[i] > model[i])
// 				return (1);
// 			else if (s[i] < model[i])
// 				return (0);
// 			else
// 				i++;
// 		}
// 		return (0);
// 	}
// }

// int	input_test_overflow(int argc, char **argv)
// {
// 	int	i;

// 	i = 0;
// 	while (i < argc)
// 	{
// 		if (argv[i][0] == '+')
// 		{
// 			if (string_is_greater(skip_zero(argv[i] + 1), "2147483647"))
// 				return (1);
// 		}
// 		else if (argv[i][0] == '-')
// 		{
// 			if (string_is_greater(skip_zero(argv[i] + 1), "2147483648"))
// 				return (1);
// 		}
// 		else if (string_is_greater(skip_zero(argv[i]), "2147483647"))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }























/*
plusieurs arg avec le premier numeric
ecrire erreur minishell: argument: too many arguments
pas de exit

plusieurs arg dont le premier est non numeric ou depasse les valeur min ou max dun long long
ecrire erreur minishell: argument: numeric numeric argument required
exit
*/

int	is_over_long_long(const char *s)
{
	int	i;

	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (i > 19)
		return (1);
	return (0);
}

long long	ft_atoll(const char *s)
{
	long long	result;
	int			sign;

	while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
		s++;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	result = 0;
	while (*s >= '0' && *s <= '9')
	{
		result = result * 10 + *s - '0';
		s++;
	}
	return (sign * result);
}

void	exit_(t_tree *tree, t_data *data)
{
	prepare_exec_relative(tree, data);
	if (data->cmd->argc > 1)
	{
		if (ft_isnumeric(data->cmd->argv[1]) == 0)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("numeric argument required\n", 2);
			free_all(data);
			exit(255);
		}
		else if (data->cmd->argc > 2)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("too many arguments\n", 2);
			free_all(data);
			exit(1);
		}
		else
		{
			ft_putstr_fd("exit\n", 2);
			free_all(data);
			exit(ft_atoi(data->cmd->argv[1]));
		}
	}
	else
	{
		free_all(data);
		exit(0);
	}
}
