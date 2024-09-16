/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:30:40 by etaattol          #+#    #+#             */
/*   Updated: 2024/06/24 18:38:54 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && *s != '\n' && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c || *s == '\n')
		{
			in_word = 0;
		}
		s++;
	}
	return (count);
}

static char	**abandon(char **words)
{
	size_t	i;

	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
	return (0);
}

static size_t	offset_of_char(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c && s[len] != '\n')
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	end_of_word;
	size_t	word_i;

	while (*s && (*s == c || *s == '\n'))
		s++;
	words = ft_calloc(word_count(s, c) + 1, sizeof(char *));
	if (!words)
		return (0);
	word_i = 0;
	while (*s)
	{
		end_of_word = offset_of_char(s, c);
		if (!end_of_word)
			end_of_word = ft_strlen(s);
		words[word_i] = ft_substr(s, 0, end_of_word);
		if (!words[word_i++])
			return (abandon(words));
		s += end_of_word;
		while (*s && (*s == c || *s == '\n'))
			s++;
	}
	return (words);
}
