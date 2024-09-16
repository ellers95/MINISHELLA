/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:52:23 by etaattol          #+#    #+#             */
/*   Updated: 2023/11/20 09:35:40 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h_i;
	size_t	n_i;

	if (!*needle)
		return ((char *)haystack);
	h_i = 0;
	while (haystack[h_i] && h_i < len)
	{
		n_i = 0;
		while (haystack[h_i + n_i] == needle[n_i] && haystack[h_i + n_i]
			&& (h_i + n_i) < len)
			n_i++;
		if (!needle[n_i])
			return ((char *)(haystack + h_i));
		h_i++;
	}
	return (NULL);
}
