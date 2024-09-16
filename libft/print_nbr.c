/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:49:46 by etaattol          #+#    #+#             */
/*   Updated: 2024/02/16 13:24:57 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_nbr(int nbr, int *check)
{
	int	count;

	count = 0;
	if (nbr == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nbr < 0)
	{
		count += print_char('-', check);
		if (count == -1)
			return (-1);
		count += print_nbr(-nbr, check);
	}
	else
	{
		if (nbr >= 10)
		{
			count += print_nbr(nbr / 10, check);
			if (count == -1)
				return (-1);
		}
		count += print_char(nbr % 10 + '0', check);
	}
	return (count);
}
