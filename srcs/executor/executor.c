/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:44:25 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/17 00:04:58 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Main execution function for the shell.
* Orchestrates the overall command execution process.
* Handles built-ins, redirections, and piped commands.
*/
bool	execution(t_data *data)
{
	if (!data->has_redirection && !data->is_pipe)
		builtins(data);
	token_merge(data);
	if (data->is_heredoc)
		get_set_stop_flag(SET, 0);
	if (data->has_redirection && !data->is_pipe)
		handle_redirections(data);
	if (data->token_count > 0)
		execute_pipeline(data);
	clean_struct(data);
	return (true);
}

/*
* Prepares and processes commands before execution.
* Handles redirections, command line parsing, and argument parsing.
*/
bool	handle_commands(t_data *data, char **envp)
{
	if (data->has_redirection)
		handle_redirections(data);
	if (!parse_command_line(data, envp))
	{
		cleanup_and_handle_errors(data);
		return (false);
	}
	if (!parse_command_arguments(data))
	{
		cleanup_and_handle_errors(data);
		return (false);
	}
	return (true);
}

/*
* Executes a single command in a child process.
* Handles command path resolution and execution using execve.
*/
void	execute_command(t_data *data, char **envp, int index)
{
	char	**command_arguments;

	command_arguments = ft_split(data->token[index], ' ');
	if (command_arguments == NULL || command_arguments[0] == NULL)
	{
		ft_printf("Failed to split command arguments\n");
		exiting(data, 1);
	}
	if (!ft_strncmp(command_arguments[0], "exit", 5))
	{
		handle_exit(data);
		free(command_arguments);
		exiting(data, 0);
	}
	if (data->command_paths[index])
	{
		execve(data->command_paths[index], command_arguments, envp);
		ft_printf("Failed to execute command: %s\n", strerror(errno));
		free_args(command_arguments);
		exiting(data, 126);
	}
	ft_printf("Command not found\n");
	free_args(command_arguments);
	exiting(data, 127);
}
