/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:12:28 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/19 08:08:49 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Performs a complete cleanup of the shell's data structures.
 * Calls clean_struct to reset the main structure, frees the environment
 * variable linked list, and deallocates the environment string array.
*/
void	clean_data(t_data *data)
{
	clean_struct(data);
	free_env(&data->env);
	free_char_array(data->envp);
}

/*
 * Frees the memory allocated for input and output file descriptors.
 * This function is part of the cleanup process, ensuring that all
 * file-related resources are properly released.
*/
static inline void	clean_files(t_data *data)
{
	if (data->input_file_fds != NULL)
	{
		ft_free(data->input_file_fds);
		data->input_file_fds = NULL;
	}
	if (data->output_file_fds != NULL)
	{
		ft_free(data->output_file_fds);
		data->output_file_fds = NULL;
	}
}

/*
 * Resets and cleans up the main data structure.
 * Frees tokens, closes file descriptors, and resets counters and flags.
 * Does not free the environment variables.
*/
void	clean_struct(t_data *data)
{
	if (data->command_arguments)
	{
		ft_free(data->command_arguments);
		data->command_arguments = NULL;
	}
	if (data->command_paths)
	{
		free_array(&data->command_paths, data->token_count);
		data->command_paths = NULL;
	}
	if (data->token_count > 0)
		remove_token_and_shift_array(data, 0);
	clean_files(data);
	data->token_count = 0;
	data->input_file_count = 0;
	data->output_file_count = 0;
	data->fd_input = -1;
	data->fd_output = -1;
	data->previous_pipe_fd[0] = -1;
	data->previous_pipe_fd[1] = -1;
}

/*
 * Frees the entire environment variable linked list.
 * Iterates through the list, freeing each node's key and value,
 * then frees the node itself.
*/
void	free_env(t_node	**env)
{
	t_node	*temp;
	t_node	*curr;

	curr = *env;
	temp = NULL;
	while (curr)
	{
		temp = curr->next;
		ft_free(curr->value);
		ft_free(curr->key);
		ft_free(curr);
		curr = temp;
	}
	*env = NULL;
}

/*
 * Cleans up file-related resources in the data structure.
 * Frees arrays holding file descriptors for input and output files.
*/
void	exiting(t_data *data, int i)
{
	clean_data(data);
	exit(i);
}
