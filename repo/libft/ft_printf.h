/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 03:37:31 by qhauuy            #+#    #+#             */
/*   Updated: 2024/04/17 14:31:24 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

/* ft_printf.c */
int		ft_printf(const char *s, ...);
int		ft_print_param(char format, va_list ap, int *error);

/* ft_print_char_and_string.c */
int		ft_print_char(int c, int *error);
int		ft_print_string(char *s, int *error);

/* ft_print_int_and_unsigned.c */
int		ft_print_int(int n, int *error);
int		ft_print_unsigned(unsigned int n, int *error);
char	*ft_itoa_unsigned(unsigned int n);
int		ft_length_unsigned(unsigned long n);

/* ft_print_hex_and_pointer.c */
int		ft_print_unsigned_hex(unsigned long n, char format, int *error);
char	*ft_itoa_unsigned_hex(unsigned long n, char format);
int		ft_length_unsigned_hex(unsigned long n);
char	ft_unit_decimal_to_hex(int n, char format);
int		ft_print_pointer(void *p, int *error);

#endif
