/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:41:46 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/17 18:57:07 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Cleans redirection symbols from token strings.
 * Removes leading '<' or '>' characters from the given string.
*/
static inline char	*remove_redirection_symbols(char *token_str)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	copy = ft_alloc(sizeof(char) * (ft_strlen(token_str) + 1));
	if (!copy)
	{
		ft_printf("ft_alloc fail in arrows");
		return (NULL);
	}
	while (token_str[i] != '\0')
	{
		while (token_str[i] == '<' || token_str[i] == '>')
			i++;
		while (token_str[i] != '\0')
		{
			copy[j] = token_str[i];
			i++;
			j++;
		}
	}
	copy[j] = '\0';
	return (copy);
}

/*
 * Handles output file redirections.
 * Processes '>' for overwrite and '>>' for append operations.
 * Opens the specified output file and updates the data structure accordingly.
*/
static inline void	handle_output_redirection(t_data *data, int i)
{
	bool	append;

	if (ft_strncmp(data->token[i], ">>", 2) == 0)
	{
		append = true;
		if (ft_strncmp(data->token[i], ">>\0", 3) != 0)
			data->token[i] = remove_redirection_symbols(data->token[i]);
		else
			remove_token_and_shift_array(data, i);
		setup_output_redirection(data, i, append);
		remove_token_and_shift_array(data, i);
	}	
	else if (ft_strncmp(data->token[i], ">", 1) == 0)
	{
		append = false;
		if (ft_strncmp(data->token[i], ">\0", 2) != 0)
			data->token[i] = remove_redirection_symbols(data->token[i]);
		else
			remove_token_and_shift_array(data, i);
		setup_output_redirection(data, i, append);
		remove_token_and_shift_array(data, i);
	}
}

/*
 * Handles input file redirections and here-documents.
 * Processes '<' for input files and '<<' for here-documents.
 * Opens input files or sets up here-documents as needed.
*/
static inline void	handle_input_redirection(t_data *data, int i)
{
	if (ft_strncmp(data->token[i], "<<", 2) == 0)
		data->token[i] = remove_redirection_symbols(data->token[i]);
	else if (ft_strncmp(data->token[i], "<", 1) == 0)
	{
		if (ft_strncmp(data->token[i], "<\0", 2) != 0)
			data->token[i] = remove_redirection_symbols(data->token[i]);
		else
			remove_token_and_shift_array(data, i);
		setup_input_redirection(data, i);
		remove_token_and_shift_array(data, i);
	}
}

/*
 * Manages file redirection operations in the shell command.
 * Iterates through tokens to handle input and output redirections.
 * Calls specific functions for input and output file operations.
*/
void	process_redirection_tokens(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i] && data->token_count > 1)
	{
		if (ft_strncmp(data->token[i], "<", 1) == 0)
			handle_input_redirection(data, i);
		else if (ft_strncmp(data->token[i], ">", 1) == 0)
			handle_output_redirection(data, i);
		else
			i++;
	}
}
