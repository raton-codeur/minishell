/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:48:25 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/15 17:41:18 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print_abs(unsigned int n, int fd)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		write(fd, &c, 1);
	}
	else
	{
		ft_print_abs(n / 10, fd);
		ft_print_abs(n % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	n_abs;

	if (n < 0)
	{
		write(fd, "-", 1);
		n_abs = -n;
	}
	else
		n_abs = n;
	ft_print_abs(n_abs, fd);
}
