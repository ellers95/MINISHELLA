/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:12:22 by etaattol          #+#    #+#             */
/*   Updated: 2023/11/20 09:36:10 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	long	len;

	ptr = (char *) s;
	len = ft_strlen(ptr);
	while (len >= 0)
	{
		if (ptr[len] == (char) c)
			return (&(ptr[len]));
		len--;
	}
	return (0);
}
