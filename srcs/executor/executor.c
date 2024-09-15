/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:44:25 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 17:50:01 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	execution(t_data *data);
bool	handle_commands(t_data *data, char **envp);
void	execute_command(t_data *data, char **envp, int index);

/*
* Main execution function for the shell.
* Orchestrates the overall command execution process.
* Handles built-ins, redirections, and piped commands.
*/
bool	execution(t_data *data)
{
	if (!data->is_rdr && !data->is_pipe)
		builtins(data);
	token_merge(data);
	if (data->is_heredoc)
		big_stopping(SET, 0);
	if (data->is_rdr && !data->is_pipe)
		redirections(data);
	if (data->tok_num > 0)
		pipex(data);
	clean_struct(data);
	return (true);
}

/*
* Prepares and processes commands before execution.
* Handles redirections, command line parsing, and argument parsing.
*/
bool	handle_commands(t_data *data, char **envp)
{
	if (data->is_rdr)
		redirections(data);
	if (!parse_cmd_line(data, envp))
	{
		clean_n_errors(data);
		return (false);
	}
	if (!parse_cmd_args(data))
	{
		clean_n_errors(data);
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
	char	**cmd_args;

	cmd_args = ft_split(data->token[index], ' ');
	if (cmd_args == NULL || cmd_args[0] == NULL)
	{
		ft_printf("Failed to split command arguments\n");
		exiting(data, 1);
	}
	if (!ft_strncmp(cmd_args[0], "exit", 5))
	{
		handle_exit(data);
		free(cmd_args);
		exiting(data, 0);
	}
	if (data->cmd_paths[index])
	{
		execve(data->cmd_paths[index], cmd_args, envp);
		ft_printf("Failed to execute command: %s\n", strerror(errno));
		free_argh(cmd_args);
		exiting(data, 126);
	}
	else
	{
		ft_printf("Command not found\n");
		free_argh(cmd_args);
		exiting(data, 127);
	}
	free_argh(cmd_args);
	exiting(data, 1);
}
