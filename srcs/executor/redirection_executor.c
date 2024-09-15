/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_executor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:46:05 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 17:55:39 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			redirections(t_data *data);
static inline void	execute_rdr(t_data *data, char **envp);
static inline void	close_files(t_data *data);
static inline void	dupper(t_data *data);

/*
* Manages the overall redirection process for a command.
* Handles both input and output redirections.
*/
void	redirections(t_data *data)
{
	if (data->tok_num < 2)
	{
		clean_struct(data);
		return ;
	}
	file_handling(data);
	if (data->is_heredoc && data->tok_num < 1)
	{
		clean_struct(data);
		return ;
	}
	if (!data->is_pipe)
	{
		execute_rdr(data, data->envp);
		while (data->tok_num > 0)
			token_cleaner(data, 0);
	}
}

/*
* Executes a command with redirections in a child process.
* Sets up redirections, executes the command, and handles cleanup.
*/
static inline void	execute_rdr(t_data *data, char **envp)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**cmd_args;

	cmd_args = NULL;
	path = NULL;
	pid = fork();
	if (pid < 0)
	{
		perror("Error not forking");
		return ;
	}
	if (pid == 0)
	{
		dupper(data);
		close_files(data);
		cmd_args = ft_split(data->token[0], ' ');
		if (cmd_args == NULL)
		{
			ft_printf("Bnanas! Failed to split the command arguments\n");
			free_stuff(cmd_args, path);
			exiting(data, 1);
		}
		path = get_path(cmd_args[0], envp);
		if (!path)
		{
			printf("%s\n", cmd_args[0]);
			builtins(data);
			perror("Error: Command is Error:");
			free_stuff(cmd_args, NULL);
			exiting(data, 126);
		}
		builtins(data);
		token_cleaner(data, 0);
		execve(path, cmd_args, envp);
		free_stuff(cmd_args, path);
		exiting(data, -1);
	}
	else
	{
		waitpid(pid, &status, 0);
		data->last_exit_status = WEXITSTATUS(status);
	}
}

/*
* Closes all opened file descriptors for redirections.
* Ensures proper cleanup after redirection operations.
*/
static inline void	close_files(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->infile_count)
	{
		close(data->in_files[i]);
		i++;
	}
	i = 0;
	while (i < data-> outfile_count)
	{
		close(data->out_files[i]);
		i++;
	}
}

/*
* Performs the actual file descriptor duplication for redirections.
* Sets up stdin and stdout to point to the appropriate files.
*/
static inline void	dupper(t_data *data)
{
	if (data->infile_count > 0)
	{
		if (dup2(data->in_files[data->infile_count - 1], STDIN_FILENO) < 0)
			exiting(data, -1);
	}
	if (data->outfile_count > 0)
	{
		if (dup2(data->out_files[data->outfile_count - 1], STDOUT_FILENO) < 0)
		{
			perror("Error! Error in dup2 OUTPUT redirections\n");
			exiting(data, -1);
		}
	}
}
