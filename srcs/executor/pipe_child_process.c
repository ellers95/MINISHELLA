/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:10:23 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/18 20:38:51 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Sets up input redirection for a command in the pipeline.
* Redirects either from a file or the previous command's output.
*/
static inline void	redirect_input(t_data *data, int index)
{
	if (index == 0 && data->fd_input != -1)
	{
		dup2(data->fd_input, STDIN_FILENO);
		close(data->fd_input);
	}
	else if (index > 0)
	{
		dup2(data->previous_pipe_fd[0], STDIN_FILENO);
		close(data->previous_pipe_fd[0]);
	}
}

/*
* Sets up output redirection for a command in the pipeline.
* Redirects either to a file or to the next command's input.
*/
static inline void	redirect_output(t_data *data, int fd[2], int index)
{
	if (index == data->token_count && data->fd_output != -1)
	{
		dup2(data->fd_output, STDOUT_FILENO);
		close(data->fd_output);
	}
	else if (index < data->token_count - 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_pipe_fds(fd);
	}
}

/*
* Manages I/O redirection and command execution in a child process.
* Handles file redirection if present, otherwise manages pipe I/O.
* Redirects input and output as needed, then executes the command.
*/
void	handle_child_process(t_data *data, char **envp,
						int command_index, int fd[2])
{
	struct sigaction	dfl;

	ft_memset(&dfl, 0, sizeof(dfl));
	dfl.sa_handler = SIG_DFL;
	dfl.sa_flags = 0;
	sigaction(SIGQUIT, &dfl, NULL);
	if (data->has_redirection)
	{
		if (!redirect_file_input(data))
			redirect_input(data, command_index);
		redirect_file_output(data);
	}
	else
	{
		redirect_input(data, command_index);
		redirect_output(data, fd, command_index);
	}
	execute_command(data, envp, command_index);
}
