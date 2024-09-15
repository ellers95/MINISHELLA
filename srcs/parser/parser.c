/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:47:18 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 19:06:00 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parser(t_data *data);
void	create_file_storage(t_data *data);
void	mallocing(t_data *data);
void	type_flagger(t_data *data);
bool	heredoc_check(t_data *data, int i);

/*
 * Creates space for the files and sets flags for pipes and redirections
 */
bool	parser(t_data *data)
{
	create_file_storage(data);
	type_flagger(data);
	return (true);
}

/*
* Count and allocate space for files
*/
static inline void	create_file_storage(t_data *data)
{
	int	i;

	data->infile_count = 0;
	data->outfile_count = 0;
	i = 0;
	while (i < data->tok_num)
	{
		if (ft_strncmp(data->token[i], "<", 1) == 0)
			data->infile_count++;
		else if (ft_strncmp(data->token[i], ">", 1) == 0
			|| ft_strncmp(data->token[i], ">>", 2) == 0)
			data->outfile_count++;
		i++;
	}
	mallocing(data);
	data->infile_count = 0;
	data->outfile_count = 0;
}

/*
* Allocating space for the files
*/
static inline void	mallocing(t_data *data)
{
	data->in_files = malloc(sizeof(int) * data->infile_count);
	if (!data->in_files)
	{
		perror("Error: Malloc in_files failed");
		return ;
	}
	data->out_files = malloc(sizeof(int) * data->outfile_count);
	if (!data->out_files)
	{
		perror("Error: Malloc out_files failed");
		free(data->in_files);
		return ;
	}
}

/*
 * Sets flags for redirections and pipes
 */
static inline void	type_flagger(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i])
	{		
		if (!heredoc_check(data, i))
			return ;
		if (ft_strncmp(data->token[i], "|", 1) == 0)
		{
			data->is_pipe = true;
		}
		if (ft_strncmp(data->token[i], ">>", 2) == 0
			|| ft_strncmp(data->token[i], ">", 1) == 0
			|| ft_strncmp(data->token[i], "<", 1) == 0)
			data->is_rdr = true;
		i++;
	}	
}

/*

*/
static inline bool	heredoc_check(t_data *data, int i)
{
	if (ft_strncmp(data->token[i], "<<", 2) == 0)
	{
		if ((ft_strncmp(data->token[i], "<<<", 3) == 0)
			|| (ft_strncmp(data->token[i], "<<>", 3) == 0)
			|| (ft_strncmp(data->token[i], "<<|", 3) == 0))
		{
			clean_struct(data);
			printf("Error: Syntax error after token <<\n");
			return (false);
		}
		data->is_heredoc = true;
		find_doc(data, i);
		if (data->tok_num < 1)
		{
			clean_struct(data);
			return (false);
		}
	}
	return (true);
}
