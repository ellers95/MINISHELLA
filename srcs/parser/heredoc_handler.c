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

//void	find_doc(t_data *data, int tk_i);
//void	handle_the_doc(const char *delimiter, t_data *data);
//char	*find_delimiter(t_data *data);
char	*readline_wrapper(const char *prompt, t_data *data);
static inline char	*clean_delimiter(char *str);

/*
 * Locates and processes a here-document in the command.
 * Identifies the delimiter and initiates the here-document 
 * handling process.
*/
void	find_doc(t_data *data, int tk_i)
{
	char	*delimiter;
	char	separate;

	separate = 0;
	if (ft_strlen(data->token[tk_i]) == 2)
	{
		delimiter = find_delimiter(data);
		separate = 1;
	}
	else
	{
		delimiter = data->token[tk_i] + 2;
		data->token[tk_i] = clean_delimiter(data->token[tk_i]);
	}
	handle_the_doc(delimiter, data);
	if (separate)
		free(delimiter);
}

/*
 * Handles the here-document input process.
 * Reads input lines until the delimiter is encountered, storing the content.
 * Sets up file descriptors for the here-document content.
*/
void	handle_the_doc(const char *delimiter, t_data *data)
{
	char	*line;
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
			free (line);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
	set_heredoc_status(OUT_HEREDOC);
	if (data->heredoc_interrupted || eof_encountered)
	{
		close(fd[0]);
		if (eof_encountered)
		{
			printf("\nminishell: warning: heredoc delimited \
					by end-of-file (wanted `%s')\n", delimiter);
		}
	}
	else
	{
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
* Searches for and extracts the delimiter for a here-document.
*/
char	*find_delimiter(t_data *data)
{
	int		i;
	int		len;
	char	*deli;

	i = 0;
	while (data->token[i])
	{
		if (!ft_strcmp(data->token[i++], "<<"))
		{
			if (!data->token[i])
				return (ft_strdup(""));
			len = ft_strlen(data->token[i]);
			deli = malloc(sizeof(char) * (len + 1));
			if (!deli)
			{
				clean_struct(data);
				return (NULL);
			}
			ft_strlcpy(deli, data->token[i], len + 1);
			token_cleaner(data, i);
			return (deli);
		}
	}
	return (NULL);
}

/*
 * A wrapper function for readline to handle interrupts during here-document input.
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
 * Cleans and formats the delimiter string for a here-document.
 * Removes any leading '<' characters from the delimiter.
*/
static inline char	*clean_delimiter(char *str)
{
	char	*copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char) * 4);
	if (!copy)
	{
		ft_printf("Error: Malloc fail in doc\n");
		return (0);
	}
	while (str[i] == '<' && str[i] != '\0')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
