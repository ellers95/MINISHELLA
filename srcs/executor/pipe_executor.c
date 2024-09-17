/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:48:47 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/17 17:20:04 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Creates a pipe and forks a new process.
*/
static inline bool	create_pipe_and_fork(t_data *data, int fd[2],
						pid_t *pid, int index)
{
	if (index < data->token_count)
	{
		if (pipe(fd) == -1)
		{
			perror("No pipes to fork the data\n");
			return (false);
		}
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("some error\n");
		if (index < data->token_count)
			close_pipe_fds(fd);
		return (false);
	}
	return (true);
}

static inline void	handle_parent_process(t_data *data, int fd[2],
						int command_index, int is_last_command)
{
	int	status;

	if (command_index > 0)
		close(data->previous_pipe_fd[0]);
	if (!is_last_command)
	{
		data->previous_pipe_fd[0] = fd[0];
		close(fd[1]);
	}
	else
	{
		close_pipe_fds(fd);
		waitpid(-1, &status, 0);
		data->last_command_exit_status = WEXITSTATUS(status);
	}
}

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

static inline void	handle_child_process(t_data *data, char **envp,
						int command_index, int fd[2])
{
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

/*
* Creates a child process for executing a command in a pipeline.
* Sets up input/output redirections and executes the command.
*/
static inline int	create_child(t_data *data, char **envp, int command_index)
{
	pid_t	pid;
	int		fd[2];
	int		is_last_command;

	is_last_command = (command_index == data->token_count - 1);
	if (!create_pipe_and_fork(data, fd, &pid, command_index))
		return (false);
	if (pid == 0)
	{
		handle_child_process(data, envp, command_index, fd);
		exit (1);
	}
	else
		handle_parent_process(data, fd, command_index, is_last_command);
	return (true);
}

/*
* Implements pipe functionality for command execution.
* Manages the creation of child processes and sets up pipes between them.
*/
void	execute_pipeline(t_data *data)
{
	int		i;
	int		status;

	status = 0;
	data->previous_pipe_fd[0] = -1;
	data->previous_pipe_fd[1] = -1;
	if (!handle_commands(data, data->envp))
	{
		ft_printf("Commands failed\n");
		return ;
	}
	i = 0;
	while (i < data->token_count)
	{
		if (!create_child(data, data->envp, i))
			return ;
		i++;
	}
	i = 0;
	while (i++ < data->token_count)
		waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		data->last_command_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->last_command_exit_status = 128 + WTERMSIG(status);
}
