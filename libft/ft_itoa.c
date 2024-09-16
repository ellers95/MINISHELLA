/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:26:45 by etaattol          #+#    #+#             */
/*   Updated: 2023/11/13 12:40:06 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lenght(int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*n_iszero_or_minint(int n)
{
	if (!n)
		return (ft_strdup("0"));
	return (ft_strdup("-2147483648"));
}

char	*ft_itoa(int n)
{
	int		len;
	char	neg;
	char	*str;

	if (!n || n == -2147483648)
		return (n_iszero_or_minint(n));
	neg = 0;
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	len = lenght(n);
	str = ft_calloc(neg + len + 1, 1);
	if (!str)
		return (0);
	if (neg)
		str[0] = '-';
	while (n)
	{
		str[neg + len -1] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (str);
}
