/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:02:32 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/18 19:11:23 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * Opens an input file for redirection or handles here-document setup.
 * If the token indicates a here-document (<<), it sets up the here-document.
 * Otherwise, it opens the specified file for input redirection.
 * Updates the data structure with the new file descriptor.
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
 * Opens an output file for redirection, either in truncate or append mode.
 * Creates the file if it doesn't exist, or opens it if it does.
 * Updates the data structure with the new file descriptor.
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
