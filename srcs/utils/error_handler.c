/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:09:55 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 00:11:25 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

*/
void	clean_n_errors(t_data *data)
{
	if (data->fd_input != -1)
		close(data->fd_input);
	if (data->fd_output != -1)
		close(data->fd_output);
	if (data->cmd_paths != NULL)
		free_line(data->cmd_paths, data->tok_num - 1);
	if (data->token != NULL)
		free_array(&data->token, data->tok_num - 1);
	free(data);
}
