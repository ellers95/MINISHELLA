/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:25:04 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/16 01:02:47 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Resets the main data structure to prepare for processing a new command.
 * Clears flags, resets counters, and frees allocated memory from previous commands.
 * Reinitializes file descriptors and other state variables.
 * Rebuilds the environment variable array from the current linked list state.
*/
void	reset_struct(t_data *data)
{
	data->is_pipe = false;
	data->has_redirection = false;
	data->is_heredoc = false;
	data->output_file_count = 0;
	data->input_file_count = 0;
	data->original_stdin = -1;
	data->heredoc_interrupted = 0;
	free_char_array(data->envp);
	data->envp = env_list_to_array(&data->env);
}
