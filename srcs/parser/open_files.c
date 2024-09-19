/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:02:32 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/19 08:16:55 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Manages the process of handling a heredoc redirection.
 * Sets heredoc status, finds the delimiter, processes heredoc content,
 * and updates the shell state accordingly.
*/
static void	handle_heredoc_redirection(t_data *data)
{
	char	*delimiter;

	set_heredoc_status(IN_HEREDOC);
	delimiter = find_delimiter(data);
	if (delimiter)
	{
		handle_heredoc(delimiter, data);
		ft_free(delimiter);
	}
	else
		printf("Error: Unable to find heredoc delimiter\n");
	set_heredoc_status(OUT_HEREDOC);
	data->is_heredoc = true;
}

/*
 * Sets up input redirection for a command,
 * handling both file input and heredocs.
 * If the token indicates a heredoc (<<),
 * it calls handle_heredoc_redirection.
 * For regular file input, it opens the file and stores the file descriptor.
*/
void	setup_input_redirection(t_data *data, int i)
{
	int		fd;

	if (ft_strncmp(data->token[i], "<<", 2) == 0)
		handle_heredoc_redirection(data);
	else if (get_heredoc_status() == OUT_HEREDOC)
	{
		fd = open(data->token[i], O_RDONLY);
		if (fd == -1)
		{
			perror("Error: Error opening input file");
			return ;
		}
		data->input_file_fds[data->input_file_count] = fd;
	}
	else
	{
		printf("Error: Unexpected token while \
					in heredoc: %s\n", data->token[i]);
		return ;
	}
	data->input_file_count++;
}

/*
 * Sets up output redirection for a command,
 * handling both truncate and append modes.
 * Opens the specified file (creating it if necessary)
 * and stores the file descriptor.
*/
void	setup_output_redirection(t_data *data, int i, bool append)
{
	int	fd;

	if (append)
		fd = open(data->token[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(data->token[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("Error!: Error opening output file");
		return ;
	}	
	data->output_file_fds[data->output_file_count] = fd;
	data->output_file_count++;
}

/*
 * Closes all open file descriptors used
 * for input and output redirection.
 * This function should be called after
 * command execution to clean up resources.
*/
void	close_files(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->input_file_count)
		close(data->input_file_fds[i++]);
	i = 0;
	while (i < (size_t)data->output_file_count)
		close(data->output_file_fds[i++]);
}
