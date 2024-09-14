/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:48:47 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/14 23:50:24 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				pipex(t_data *data);
static inline int	create_child(t_data *data, char **envp, int index);
static inline bool	fork_it(t_data *data, int fd[2], pid_t *pid, int index);
static inline void	redirect_input(t_data *data, int index);
static inline void	redirect_output(t_data *data, int fd[2], int index);

/*
* Implements pipe functionality for command execution.
* Manages the creation of child processes and sets up pipes between them.
*/
void	pipex(t_data *data)
{
	int		i;
	int		status;

	data->prev_fd[0] = -1;
	data->prev_fd[1] = -1;
	if (!handle_commands(data, data->envp))
	{
		ft_printf("Commands failed\n");
		return ;
	}
	i = 0;
	while (i < data->tok_num)
	{
		if (!create_child(data, data->envp, i))
			return ;
		i++;
	}
	i = 0;
	while (i < data->tok_num)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	if (WIFEXITED(status))
        data->last_exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status)) 
        data->last_exit_status = 128 + WTERMSIG(status);
}

/*
* Creates a child process for executing a command in a pipeline.
* Sets up input/output redirections and executes the command.
*/
static inline int	create_child(t_data *data, char **envp, int index)
{
	pid_t	pid;
	int		fd[2];
	int		last;
	int		status;

	last = (index == data->tok_num) -1;

	if (!fork_it(data, fd, &pid, index))
		return (false);
	if (pid == 0)
	{
		if(data->is_rdr)
		{
			if(!redirect_file_input(data))
				redirect_input(data, index);
			redirect_file_output(data);
		}
		else
		{
			redirect_input(data, index);
			redirect_output(data, fd, index);
		}
		execute_command(data, envp, index);
		exit (1);
	}
	else
	{
		if (index > 0)
			close(data->prev_fd[0]);

		if (!last)
		{
			data->prev_fd[0] = fd[0];
			close(fd[1]);
		}
		else
		{
			shut_fd(fd);
			waitpid(pid, &status, 0);
			data->last_exit_status = WEXITSTATUS(status);
		}
	}
	return (true);
}

/*
* Creates a pipe and forks a new process.
*/
static inline bool	fork_it(t_data *data, int fd[2], pid_t *pid, int index)
{
	if (index < data->tok_num)
	{
		if(pipe(fd) == -1)
		{
			perror("No pipes to fork the data\n");
			return (false);
		}
	}

	*pid = fork();
	if (*pid == -1)
	{
		perror("some error\n");
		if (index < data->tok_num)
			shut_fd(fd);
		return (false);
	}
	return (true);
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
		dup2(data->prev_fd[0], STDIN_FILENO);
		close(data->prev_fd[0]);
	}
}

/*
* Sets up output redirection for a command in the pipeline.
* Redirects either to a file or to the next command's input.
*/
static inline void	redirect_output(t_data *data, int fd[2], int index)
{
	if (index == data->tok_num && data->fd_output != -1)
	{
		dup2(data->fd_output, STDOUT_FILENO);
		close(data->fd_output);
	}
	else if (index < data->tok_num - 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		shut_fd(fd);
	}
}