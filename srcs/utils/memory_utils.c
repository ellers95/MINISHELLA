/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:12:28 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 19:06:43 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_data(t_data *data);
void	clean_struct(t_data *data);
void	free_env(t_node	**env);
void	clean_files(t_data *data);
void	exiting(t_data *data, int i);

/*

*/
void	clean_data(t_data *data)
{
	clean_struct(data);
	free_env(&data->env);
	free_char_array(data->envp);
}

/*

*/
void	clean_struct(t_data *data)
{
	if (data->tok_num > 0)
		token_cleaner(data, 0);
	clean_files(data);
	if (data->pipes != NULL)
	{
		free(data->pipes);
		data->pipes = NULL;
	}
	data->tok_num = 0;
	data->infile_count = 0;
	data->outfile_count = 0;
	data->fd_input = -1;
	data->fd_output = -1;
	data->prev_fd[0] = -1;
	data->prev_fd[1] = -1;
}

/*

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
		free(curr->value);
		free(curr->key);
		free(curr);
		curr = temp;
	}
	*env = NULL;
}

/*

*/
static inline void	clean_files(t_data *data)
{
	if (data->in_files != NULL)
	{
		free(data->in_files);
		data->in_files = NULL;
	}
	if (data->out_files != NULL)
	{
		free(data->out_files);
		data->out_files = NULL;
	}
}

/*

*/
void	exiting(t_data *data, int i)
{
	clean_data(data);
	exit(i);
}
