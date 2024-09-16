/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:12:19 by etaattol          #+#    #+#             */
/*   Updated: 2024/02/16 13:24:51 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_hex(unsigned long nbr, int cap, int *check)
{
	int	count;

	count = 0;
	if (nbr >= 16)
	{
		count += print_hex((nbr / 16), cap, check);
		if (count == -1)
			return (-1);
		count += print_hex((nbr % 16), cap, check);
		if (count == -1)
			return (-1);
	}
	if ((cap == 0) && (nbr >= 10 && nbr <= 15))
		count += print_char(nbr + 87, check);
	if ((cap == 1) && (nbr >= 10 && nbr <= 15))
		count += print_char(nbr + 55, check);
	if (nbr < 10)
		count += print_nbr(nbr, check);
	return (count);
}
