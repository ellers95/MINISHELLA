/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:47:18 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/16 15:02:16 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	create_file_storage(t_data *data);
static inline void	allocate_file_descriptors(t_data *data);
static inline void	type_flagger(t_data *data);
static inline bool	is_valid_heredoc_syntax(t_data *data, int i);

/*
 * Main parsing function for the shell input.
 * Coordinates the parsing process, including 
 * file storage creation and token type flagging.
 */
bool	parser(t_data *data)
{
	create_file_storage(data);
	type_flagger(data);
	return (true);
}

/*
 * Prepares storage for input and output files.
 * Counts the number of input and output redirections in the command.
 * Allocates memory for storing file descriptors based on the counts.
*/
static inline void	create_file_storage(t_data *data)
{
	int	i;

	data->input_file_count = 0;
	data->output_file_count = 0;
	i = 0;
	while (i < data->token_count)
	{
		if (ft_strncmp(data->token[i], "<", 1) == 0)
			data->input_file_count++;
		else if (ft_strncmp(data->token[i], ">", 1) == 0
			|| ft_strncmp(data->token[i], ">>", 2) == 0)
			data->output_file_count++;
		i++;
	}
	allocate_file_descriptors(data);
	data->input_file_count = 0;
	data->output_file_count = 0;
}

/*
 * Allocates memory for storing file descriptors.
 * Creates arrays for input and output file descriptors 
 * based on counted redirections.
*/
static inline void	allocate_file_descriptors(t_data *data)
{
	data->input_file_fds = malloc(sizeof(int) * data->input_file_count);
	if (!data->input_file_fds)
	{
		perror("Error: Malloc input_file_fds failed");
		return ;
	}
	data->output_file_fds = malloc(sizeof(int) * data->output_file_count);
	if (!data->output_file_fds)
	{
		perror("Error: Malloc output_file_fds failed");
		free(data->input_file_fds);
		return ;
	}
}

/*
 * Sets flags for different types of shell operations.
 * Identifies and marks pipes, redirections, and 
 * here-documents in the command.
 */
static inline void	type_flagger(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i])
	{		
		if (!is_valid_heredoc_syntax(data, i))
			return ;
		if (ft_strncmp(data->token[i], "|", 1) == 0)
		{
			data->is_pipe = true;
		}
		if (ft_strncmp(data->token[i], ">>", 2) == 0
			|| ft_strncmp(data->token[i], ">", 1) == 0
			|| ft_strncmp(data->token[i], "<", 1) == 0)
			data->has_redirection = true;
		i++;
	}	
}

/*
 * Checks and handles here-document syntax.
 * Verifies the correct format of here-document delimiters.
 * Initiates here-document processing if syntax is correct.
*/
static inline bool	is_valid_heredoc_syntax(t_data *data, int i)
{
	if (ft_strncmp(data->token[i], "<<", 2) == 0)
	{
		if ((ft_strncmp(data->token[i], "<<<", 3) == 0)
			|| (ft_strncmp(data->token[i], "<<>", 3) == 0)
			|| (ft_strncmp(data->token[i], "<<|", 3) == 0))
		{
			clean_struct(data);
			printf("Error: Syntax error after token <<\n");
			return (false);
		}
		data->is_heredoc = true;
		find_heredoc(data, i);
		if (data->token_count < 1)
		{
			clean_struct(data);
			return (false);
		}
	}
	return (true);
}
