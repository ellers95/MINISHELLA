/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:09:16 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/17 18:57:07 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	dest = ft_alloc(sizeof(char) * (s1len + s2len + 1));
	if (dest == NULL)
		return (NULL);
	if (s1)
		ft_strlcpy(dest, s1, s1len + 1);
	ft_strlcat(dest, s2, (s1len + s2len + 1));
	return (dest);
}
