/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:23:16 by etaattol          #+#    #+#             */
/*   Updated: 2024/06/30 17:26:22 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_gnl(size_t count, size_t size)
{
	void			*p;
	size_t			bsize;
	unsigned char	*ptr;

	bsize = count * size;
	if (count != 0 && bsize / count != size)
		return (NULL);
	p = malloc(bsize);
	if (p == NULL)
		return (NULL);
	ptr = (unsigned char *)p;
	while (bsize > 0)
	{
		*ptr = 0;
		ptr++;
		bsize--;
	}
	return (p);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen_gnl(s1);
	s2len = ft_strlen_gnl(s2);
	dest = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!dest)
		return (NULL);
	ft_memcpy_gnl(dest, s1, s1len);
	ft_memcpy_gnl(dest + s1len, s2, s2len + 1);
	return (dest);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy_gnl(void *dst, const void *src, size_t n)
{
	if (src != dst)
	{
		while (n--)
			((unsigned char *) dst)[n] = ((const unsigned char *) src)[n];
	}
	return (dst);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (*s == (char)c)
	{
		return ((char *)s);
	}
	return (NULL);
}
