/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:51:44 by iniska            #+#    #+#             */
/*   Updated: 2024/09/04 16:58:18 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		c;
	char	*copy;

	if (!s1 || !s2)
        return (NULL);
	i = 0;
	c = 0;
	copy = (char *)malloc(sizeof(char) * (ft_strlen(s1) + (ft_strlen(s2) +1)));
	if (!copy)
		return (NULL);
	while (s1[i] != '\0')
	{
		copy[c] = s1[i];
		c++;
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		copy[c] = s2[i];
		c++;
		i++;
	}
	copy[c] = '\0';
	return (copy);
}
