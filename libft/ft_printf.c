/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:45:42 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/04 17:21:37 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

int	format(char *specifier, va_list arg_list, int *check)
{
	int	count;

	count = 0;
	if (*specifier == 'c')
		count += print_char(va_arg(arg_list, int), check);
	else if (*specifier == 's')
		count += print_str(va_arg(arg_list, char *), check);
	else if (*specifier == 'd' || *specifier == 'i')
		count += print_nbr(va_arg(arg_list, int), check);
	else if (*specifier == 'u')
		count += print_unsigned_nbr(va_arg(arg_list, unsigned int), check);
	else if (*specifier == 'x')
		count += print_hex(va_arg(arg_list, unsigned int), 0, check);
	else if (*specifier == 'X')
		count += print_hex(va_arg(arg_list, unsigned int), 1, check);
	else if (*specifier == '%')
		count += write(1, "%", 1);
	else if (*specifier == 'p')
		count += print_ptr(va_arg(arg_list, void *), check);
	else
		return (-1);
	return (count);
}

int	ft_printf(const char *s1, ...)
{
	va_list	arg_list;
	int		count;
	int		check;
	char	*s;

	s = (char *)s1;
	check = 0;
	va_start(arg_list, s1);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			count = format(s, arg_list, &check);
		}
		else
			count = write(1, s, 1);
		if (count == -1)
			return (-1);
		s++;
		check += count;
	}
	va_end(arg_list);
	return (check);
}
