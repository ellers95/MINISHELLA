/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:11:07 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/17 18:57:07 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	forw;
	size_t	backw;
	char	*res;

	if ((set && set[0] == 0) || (s1 && s1[0] == 0))
		return (ft_strdup(s1));
	res = 0;
	if (s1 != 0 && set != 0)
	{
		forw = 0;
		backw = ft_strlen(s1);
		while (s1[forw] && ft_strchr(set, s1[forw]))
			forw++;
		while (s1[backw - 1] && ft_strchr(set, s1[backw - 1]) && backw > forw)
			backw--;
		res = ft_alloc(sizeof(char) * (backw - forw + 1));
		if (res == NULL)
			return (NULL);
		ft_strlcpy(res, s1 + forw, backw - forw + 1);
	}
	return (res);
}
