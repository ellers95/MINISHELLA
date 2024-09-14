/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:34:15 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 00:06:52 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				token_merge(t_data *data);
void				token_cleaner(t_data *data, int i);
static inline bool	valid(t_data *data, int j);
static inline void	merge_it(t_data *data, int i, int j);
bool				check_specials(char *token);

/*
* Merges adjacent tokens that should be considered as a single unit.
* Useful for handling multi-word arguments or quoted strings.
*/
void	token_merge(t_data *data)
{
	int	i;
	int	j;
	i = 0;
	while (i < data->tok_num)
	{
		if (valid(data, i))
		{
			j = i + 1;
			while (valid(data, j))
				merge_it(data, i, j);	
		}
		i++;

	}
}

/*

*/
void token_cleaner(t_data *data, int i)
{
	free(data->token[i]);
	while (i < data->tok_num - 1)
	{
		data->token[i] = data->token[i + 1];
		i++;	
	}
	data->tok_num--;
	data->token[data->tok_num] = NULL;
	if (data->tok_num == 0)
		free(data->token);
}

/*

*/
static inline bool valid(t_data *data, int j)
{
	if ((j < data->tok_num) && 
		(ft_strncmp(data->token[j], "|", 1) != 0) && 
		(ft_strncmp(data->token[j], "<", 1) != 0) && 
		(ft_strncmp(data->token[j], ">", 1) != 0))
		{
			if (data->is_rdr)
			{
				if (ft_strncmp(data->token[j], "echo\0", 5) != 0)
					return (true);
				else
					return (false);
			}
			return (true);
		}
	else
		return (false);
}

/*

*/
static inline void merge_it(t_data *data, int i, int j)
{
	int		len;
	char	*new_str;

	if((ft_strncmp(data->token[i], "<", 1)) == 0 || (ft_strncmp(data->token[i], ">", 1) == 0))
		return ;
	len = ft_strlen(data->token[i]) + ft_strlen(data->token[j]) + 2;
	new_str = (char *)ft_calloc(len, sizeof(char));
	if (new_str == NULL)
	{
		ft_printf("Calloc fail in merge\n");
		exiting(data, 1);
	}
	ft_strlcpy(new_str, data->token[i], len);
	ft_strlcat(new_str, " ", len);
	ft_strlcat(new_str, data->token[j], len);
	free(data->token[i]);
	data->token[i] = new_str; 
	if (j < data->tok_num && ((ft_strcmp(data->token[i], "|") != 0) ||
	ft_strncmp(data->token[i], "<", 1) != 0 ||
	ft_strncmp(data->token[i], ">", 1) != 0 ||
	ft_strncmp(data->token[i], "echo\0", 5) != 0))
    	token_cleaner(data, j);
}

/*

*/
bool	check_specials(char *token)
{
	if (ft_strcmp(token, "|") == 0 
		|| ft_strcmp(token, ">") == 0 
			|| ft_strcmp(token, ">>") == 0)
		return (true);	
	return (false);
}
