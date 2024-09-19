/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:19:18 by iniska            #+#    #+#             */
/*   Updated: 2024/09/14 17:20:00 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * A wrapper function for readline to handle interrupts
 * during here-document input.
 * It checks for interruption flags after reading a line
 * and handles them appropriately.
*/
char	*readline_wrapper(const char *prompt, t_data *data)
{
	char	*line;

	line = readline(prompt);
	if (get_set_stop_flag(GET, 0))
	{
		free(line);
		data->heredoc_interrupted = 1;
		return (NULL);
	}
	return (line);
}

/*
 * Reads input for a heredoc until the delimiter
 * is encountered or EOF is reached.
 * Handles interruptions and writes the heredoc content
 * to the provided file descriptor.
*/
static bool	read_heredoc_input(const char *delimiter, int fd, t_data *data)
{
	char	*line;
	bool	eof_encountered;

	eof_encountered = false;
	while (1)
	{
		line = readline_wrapper("here_doc> ", data);
		if (!line)
		{
			if (get_set_stop_flag(GET, 0))
				data->heredoc_interrupted = 1;
			else
				eof_encountered = true;
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (eof_encountered);
}

/*
* Finalizes the heredoc process after all input has been read.
 * Handles cleanup, error reporting,
 * and setting up file descriptors for the heredoc content.
*/
static void	handle_heredoc_completion(int fd[2], bool eof_encountered,
			const char *delimiter, t_data *data)
{
	set_heredoc_status(OUT_HEREDOC);
	if (data->heredoc_interrupted)
		close(fd[0]);
	else
	{
		if (eof_encountered)
		{
			printf("\nminishell: warning: heredoc delimitedby end-of-file ");
			printf("(wanted `%s')\n", delimiter);
		}
		data->input_file_fds[data->input_file_count] = fd[0];
		data->input_file_count++;
	}
	if (data->original_stdin != -1)
	{
		dup2(data->original_stdin, STDIN_FILENO);
		close(data->original_stdin);
		data->original_stdin = -1;
	}
}

/*
 * Main function for processing a heredoc.
 * Sets up the necessary pipes and file descriptors, reads the heredoc input,
 * and handles the completion of the heredoc process.
*/
void	handle_heredoc(const char *delimiter, t_data *data)
{
	int		fd[2];
	bool	eof_encountered;

	data->original_stdin = dup(STDIN_FILENO);
	if (data->original_stdin == -1)
	{
		perror("Error: Failed to duplicate STDIN\n");
		return ;
	}
	if (pipe(fd) == -1)
	{
		perror("Error: pipe");
		return ;
	}
	data->heredoc_interrupted = 0;
	set_heredoc_status(IN_HEREDOC);
	get_set_stop_flag(SET, 0);
	eof_encountered = read_heredoc_input(delimiter, fd[1], data);
	close(fd[1]);
	handle_heredoc_completion(fd, eof_encountered, delimiter, data);
}

/*
 * Identifies a heredoc in the command tokens and initiates its processing.
 * Determines the delimiter and calls handle_heredoc
 * to process the heredoc content.
*/
void	find_heredoc(t_data *data, int token_index)
{
	char	*delimiter;
	bool	is_seperate_delimiter;

	is_seperate_delimiter = false;
	if (ft_strlen(data->token[token_index]) == 2)
	{
		delimiter = find_delimiter(data);
		is_seperate_delimiter = true;
	}
	else
	{
		delimiter = data->token[token_index] + 2;
		data->token[token_index] = clean_delimiter(data->token[token_index]);
	}
	handle_heredoc(delimiter, data);
	if (is_seperate_delimiter)
		ft_free(delimiter);
}
