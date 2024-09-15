/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:25:04 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 18:45:02 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

*/
void	reset_struct(t_data *data)
{
	data->is_pipe = false;
	data->is_rdr = false;
	data->is_heredoc = false;
	data->outfile_count = 0;
	data->infile_count = 0;
	data->original_stdin = -1;
	data->heredoc_interrupted = 0;
	free_char_array(data->envp);
	data->envp = list_to_eepie(&data->env);
}
