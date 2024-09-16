/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_nbr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:50:20 by etaattol          #+#    #+#             */
/*   Updated: 2024/02/16 13:23:40 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_unsigned_nbr(unsigned int unbr, int *check)
{
	int	count;

	count = 0;
	if (unbr == 2147483647)
		return (write(1, "2147483647", 10));
	else
	{
		if (unbr >= 10)
		{
			count += print_unsigned_nbr(unbr / 10, check);
			if (count == -1)
				return (-1);
		}
		count += print_char(unbr % 10 + '0', check);
	}
	return (count);
}
