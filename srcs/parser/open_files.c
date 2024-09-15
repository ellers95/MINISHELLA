/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:02:32 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/16 00:00:26 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_infile(t_data *data, int i);
void	open_outfile(t_data *data, int i, bool append);

/*
 * Opens an input file for redirection or handles here-document setup.
 * If the token indicates a here-document (<<), it sets up the here-document.
 * Otherwise, it opens the specified file for input redirection.
 * Updates the data structure with the new file descriptor.
*/
void	open_infile(t_data *data, int i)
{
	int		fd;
	char	*delimiter;

	if (ft_strncmp(data->token[i], "<<", 2) == 0)
	{
		set_heredoc_status(IN_HEREDOC);
		delimiter = find_delimiter(data);
		if (delimiter)
		{
			handle_the_doc(delimiter, data);
			free(delimiter);
		}
		else
			ft_printf("Error: Unable to find heredoc delimiter\n");
		set_heredoc_status(OUT_HEREDOC);
		data->is_heredoc = true;
	}
	else if (get_heredoc_status() == OUT_HEREDOC)
	{
		fd = open(data->token[i], O_RDONLY);
		if (fd == -1)
		{
			perror("Error!");
			return ;
		}
		data->in_files[data->infile_count] = fd;
	}
	else
	{
		ft_printf("Error: Unexpected token while \
					in heredoc: %s\n", data->token[i]);
		return ;
	}
	data->infile_count++;
}

/*
 * Opens an output file for redirection, either in truncate or append mode.
 * Creates the file if it doesn't exist, or opens it if it does.
 * Updates the data structure with the new file descriptor.
*/
void	open_outfile(t_data *data, int i, bool append)
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
	data->out_files[data->outfile_count] = fd;
	data->outfile_count++;
}
