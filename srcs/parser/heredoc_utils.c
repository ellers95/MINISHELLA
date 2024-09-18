/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:08:13 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/18 17:07:51 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Searches for and extracts the delimiter for a here-document.
*/
char	*find_delimiter(t_data *data)
{
	int		i;
	int		len;
	char	*deli;

	i = 0;
	while (data->token[i])
	{
		if (!ft_strcmp(data->token[i++], "<<"))
		{
			if (!data->token[i])
				return (ft_strdup(""));
			len = ft_strlen(data->token[i]);
			deli = ft_alloc(sizeof(char) * (len + 1));
			if (!deli)
			{
				clean_struct(data);
				return (NULL);
			}
			ft_strlcpy(deli, data->token[i], len + 1);
			remove_token_and_shift_array(data, i);
			return (deli);
		}
	}
	return (NULL);
}

/*
 * Cleans and formats the delimiter string for a here-document.
 * Removes any leading '<' characters from the delimiter.
*/
char	*clean_delimiter(char *str)
{
	char	*copy;
	int		i;

	i = 0;
	while (str[i] == '<' && str[i] != '\0')
		i++;
	copy = ft_alloc(sizeof(char) * (i + 1));
	if (!copy)
	{
		printf("Error: ft_alloc fail in doc\n");
		return (NULL);
	}
	ft_strlcpy(copy, str, i + 1);
	return (copy);
}
