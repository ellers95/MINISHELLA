/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:41:28 by etaattol          #+#    #+#             */
/*   Updated: 2024/02/16 13:25:04 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_ptr(void *ptr, int *check)
{
	int	count;

	count = 0;
	count += print_str("0x", check);
	if (count == -1)
		return (-1);
	count += print_hex((unsigned long)ptr, 0, check);
	return (count);
}
