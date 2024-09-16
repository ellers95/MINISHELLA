/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:12:31 by etaattol          #+#    #+#             */
/*   Updated: 2023/11/20 09:28:32 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (src != dst)
	{
		while (n--)
			((unsigned char *) dst)[n] = ((const unsigned char *) src)[n];
	}
	return (dst);
}
