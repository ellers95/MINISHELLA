/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:41:46 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 00:07:42 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				file_handling(t_data *data);
static inline void	to_files(t_data *data, int i);
static inline void	from_files(t_data *data, int i);
static inline char	*clean_arrows(char *str);

/*

*/
void	file_handling(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i] && data->tok_num > 1)
	{
		if (ft_strncmp(data->token[i], "<", 1) == 0)
			from_files(data, i);
		else if (ft_strncmp(data->token[i], ">", 1) == 0)
			to_files(data, i);
		else
			i++;
	}
}

/*

*/
static inline void	to_files(t_data *data, int i)
{
	bool	append;

	if (ft_strncmp(data->token[i], ">>", 2) == 0)
	{
		append = true;
		if (ft_strncmp(data->token[i], ">>\0", 3) != 0)
			data->token[i] = clean_arrows(data->token[i]);
		else
			token_cleaner(data, i);
		open_outfile(data, i, append);
		token_cleaner(data, i);
	}	
	else if (ft_strncmp(data->token[i], ">", 1) == 0)
	{
		append = false;
		if (ft_strncmp(data->token[i], ">\0", 2) != 0)
			data->token[i] = clean_arrows(data->token[i]);
		else
			token_cleaner(data, i);
		open_outfile(data, i, append);
		token_cleaner(data, i);
	}
}

/*

*/
static inline void	from_files(t_data *data, int i)
{
	if (ft_strncmp(data->token[i], "<<", 2) == 0)
		data->token[i] = clean_arrows(data->token[i]);
	else if (ft_strncmp(data->token[i], "<", 1) == 0)
	{
		if (ft_strncmp(data->token[i], "<\0", 2) != 0)
			data->token[i] = clean_arrows(data->token[i]);
		else
			token_cleaner(data, i);
		open_infile(data, i);
		token_cleaner(data, i);
	}
}

/*

*/
static inline char	*clean_arrows(char *str)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	copy = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!copy)
	{
		ft_printf("Malloc fail in arrows");
		return (NULL);
	}
	while (str[i] != '\0')
	{
		while (str[i] == '<' || str[i] == '>')
			i++;
		while (str[i] != '\0')
		{
			copy[j] = str[i];
			i++;
			j++;
		}
	}
	copy[j] = '\0';
	return (copy);
}
