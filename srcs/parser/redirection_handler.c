/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:41:46 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/16 00:05:45 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_handling(t_data *data);
void	to_files(t_data *data, int i);
void	from_files(t_data *data, int i);
char	*clean_arrows(char *str);

/*
 * Manages file redirection operations in the shell command.
 * Iterates through tokens to handle input and output redirections.
 * Calls specific functions for input and output file operations.
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
 * Handles output file redirections.
 * Processes '>' for overwrite and '>>' for append operations.
 * Opens the specified output file and updates the data structure accordingly.
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
 * Handles input file redirections and here-documents.
 * Processes '<' for input files and '<<' for here-documents.
 * Opens input files or sets up here-documents as needed.
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
 * Cleans redirection symbols from token strings.
 * Removes leading '<' or '>' characters from the given string.
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
