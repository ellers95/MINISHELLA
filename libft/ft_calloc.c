/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:56:24 by etaattol          #+#    #+#             */
/*   Updated: 2024/06/13 13:50:01 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	bsize;

	bsize = count * size;
	if (bsize < count && bsize < size)
		return (NULL);
	p = (void *)malloc(bsize);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, bsize);
	return (p);
}
