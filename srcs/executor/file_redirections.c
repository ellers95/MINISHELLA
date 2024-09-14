/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:59:40 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/14 23:49:53 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	redirect_file_input(t_data *data);
bool	redirect_file_output(t_data *data);

/*
 * Redirects input from a file to standard input.
 * Uses the first file descriptor in data->in_files array.
*/
bool	redirect_file_input(t_data *data)
{
	int	fd;

	if (data->infile_count > 0)
	{
		fd = data->in_files[0];
		if (fd != -1)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("Error: Failed to redirect input to file\n");
				exit(EXIT_FAILURE);
			}
			close(fd);
			return (true);
		}
	}
	return (false);
}

/*
* Redirects output to a file from standard output.
* Uses the last file descriptor in data->out_files array.
*/
bool	redirect_file_output(t_data *data)
{
	int	fd;

	if (data->outfile_count > 0)
	{
		fd = data->out_files[data->outfile_count - 1];
		if (fd != -1)
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("Error: Failed to redirect output to file");
				exit(EXIT_FAILURE);
			}
			close(fd);
			return (true);
		}
	}
	return (false);
}
