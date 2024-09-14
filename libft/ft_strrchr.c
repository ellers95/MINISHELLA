/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 09:20:04 by iniska            #+#    #+#             */
/*   Updated: 2024/08/08 16:40:45 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*chr;
	char	*f;

	chr = (char *)s;
	f = (NULL);
	while (*chr != '\0')
	{
		if (*chr == (char)c)
		{
			f = chr;
			chr++;
		}
		else
			chr++;
	}
	if ((char)c == '\0')
		return (chr);
	else
		return (f);
}
