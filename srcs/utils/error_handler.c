/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:09:55 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/17 18:58:06 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Performs cleanup operations and handles errors in the shell.
 * Closes open file descriptors, frees allocated memory for command paths and tokens,
 * and releases the main data structure.
 * This function is typically called when encountering errors or during shell shutdown.
*/
void	cleanup_and_handle_errors(t_data *data)
{
	if (data->fd_input != -1)
		close(data->fd_input);
	if (data->fd_output != -1)
		close(data->fd_output);
	if (data->command_paths != NULL)
		free_line(data->command_paths, data->token_count - 1);
	if (data->token != NULL)
		free_array(&data->token, data->token_count - 1);
	ft_free(data);
}
