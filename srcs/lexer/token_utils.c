/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:34:15 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/16 11:49:44 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void			token_merge(t_data *data);
//void			token_cleaner(t_data *data, int i);
static inline bool	valid(t_data *data, int j);
static inline void	merge_it(t_data *data, int i, int j);
//bool			check_specials(char *token);

/*
* Merges adjacent tokens that should be considered as a single unit.
* Useful for handling multi-word arguments or quoted strings.
*/
void	token_merge(t_data *data)
{
	int	main_token_index;
	int	merge_token_index;

	main_token_index = 0;
	while (main_token_index < data->token_count)
	{
		if (valid(data, main_token_index))
		{
			merge_token_index = main_token_index + 1;
			while (valid(data, merge_token_index))
				merge_it(data, main_token_index, merge_token_index);
		}
		main_token_index++;
	}
}

/*
* Removes the token at index i and shifts remaining tokens.
* Used to clean up the token array after processing.
*/
void	token_cleaner(t_data *data, int i)
{
	free(data->token[i]);
	while (i < data->token_count - 1)
	{
		data->token[i] = data->token[i + 1];
		i++;
	}
	data->token_count--;
	data->token[data->token_count] = NULL;
	if (data->token_count == 0)
		free(data->token);
}

/*
* Checks if the token at index j is eligible for merging.
* Considers token type and surrounding context.
*/
static inline bool	valid(t_data *data, int j)
{
	if ((j < data->token_count)
		&& (ft_strncmp(data->token[j], "|", 1) != 0)
		&& (ft_strncmp(data->token[j], "<", 1) != 0)
		&& (ft_strncmp(data->token[j], ">", 1) != 0))
	{
		if (data->has_redirection)
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
* Combines tokens at indices i and j into a single token.
* Updates the data structure accordingly.
*/
static inline void	merge_it(t_data *data, int i, int j)
{
	int		len;
	char	*new_str;

	if ((ft_strncmp(data->token[i], "<", 1)) == 0
		|| (ft_strncmp(data->token[i], ">", 1) == 0))
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
	if (j < data->token_count && ((ft_strcmp(data->token[i], "|") != 0)
			|| ft_strncmp(data->token[i], "<", 1) != 0
			|| ft_strncmp(data->token[i], ">", 1) != 0
			|| ft_strncmp(data->token[i], "echo\0", 5) != 0))
		token_cleaner(data, j);
}

/*
* Identifies if a token contains special shell characters.
* Checks for operators, redirections, etc.
*/
bool	check_specials(char *token)
{
	if (ft_strcmp(token, "|") == 0
		|| ft_strcmp(token, ">") == 0
		|| ft_strcmp(token, ">>") == 0)
		return (true);
	return (false);
}
