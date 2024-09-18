/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_executor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:46:05 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/18 17:40:25 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Sets up file descriptors for input and output redirections.
* Duplicates appropriate FDs to stdin and stdout.
*/
static inline void	setup_redirection_file_descriptors(t_data *data)
{
	if (data->input_file_count > 0)
	{
		if (dup2(data->input_file_fds[data->input_file_count - 1],
				STDIN_FILENO) < 0)
			exiting(data, -1);
	}
	if (data->output_file_count > 0)
	{
		if (dup2(data->output_file_fds[data->output_file_count - 1],
				STDOUT_FILENO) < 0)
		{
			perror("Error! Error in dup2 OUTPUT redirections\n");
			exiting(data, -1);
		}
	}
}

/*
* Closes all opened file descriptors for redirections.
* Ensures proper cleanup after redirection operations.
*/
static inline void	close_redirection_files(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input_file_count)
	{
		close(data->input_file_fds[i]);
		i++;
	}
	i = 0;
	while (i < data-> output_file_count)
	{
		close(data->output_file_fds[i]);
		i++;
	}
}

/*
* Executes a command in a child process with redirections.
* Sets up redirections, prepares command arguments,
* and executes the command.
*/
static inline void	execute_child_with_redirections(t_data *data, char **envp)
{
	char	*path;
	char	**command_arguments;

	setup_redirection_file_descriptors(data);
	close_redirection_files(data);
	command_arguments = ft_split(data->token[0], ' ');
	if (command_arguments == NULL)
	{
		printf("Error: Failed to split the command arguments\n");
		free_stuff(command_arguments, NULL);
		exiting(data, 1);
	}
	path = get_command_path(command_arguments[0], envp);
	if (!path)
	{
		printf("%s\n", command_arguments[0]);
		builtins(data);
		perror("Error: Command is Error:");
		free_stuff(command_arguments, NULL);
		exiting(data, 126);
	}
	builtins(data);
	remove_token_and_shift_array(data, 0);
	execve(path, command_arguments, envp);
	free_stuff(command_arguments, path);
}

/*
* Executes a command with redirections in a child process.
* Sets up redirections, executes the command, and handles cleanup.
*/
static inline void	execute_command_with_redirections(t_data *data, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("Error not forking");
		return ;
	}
	if (pid == 0)
	{
		execute_child_with_redirections(data, envp);
		exiting(data, -1);
	}
	else
	{
		waitpid(pid, &status, 0);
		data->last_command_exit_status = WEXITSTATUS(status);
	}
}

/*
* Manages the overall redirection process for a command.
* Handles both input and output redirections.
*/
void	handle_redirections(t_data *data)
{
	if (data->token_count < 2)
	{
		clean_struct(data);
		return ;
	}
	process_redirection_tokens(data);
	if (data->is_heredoc && data->token_count < 1)
	{
		clean_struct(data);
		return ;
	}
	if (!data->is_pipe)
	{
		execute_command_with_redirections(data, data->envp);
		while (data->token_count > 0)
			remove_token_and_shift_array(data, 0);
	}
}
