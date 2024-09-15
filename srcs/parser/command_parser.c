/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:46:37 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 23:55:43 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_cmd_args(t_data *data);
bool	parse_cmd_line(t_data *data, char **envp);
bool	init_path(t_data *data);

/*
 * Parses command arguments from the token array.
 * Allocates memory for and populates the cmd_args array 
 * in the data structure.
 * Returns true if parsing is successful, false otherwise.
*/
bool	parse_cmd_args(t_data *data)
{
	int		i;
	char	**args;

	data->cmd_args = ft_calloc(data->tok_num, sizeof(char **));
	if (!data->cmd_args)
		return (false);
	i = 0;
	while (i < data->tok_num - 1)
	{
		args = ft_split(data->token[i], ' ');
		if (!args)
		{
			free_array(&(data->cmd_args), i);
			data->cmd_args = NULL;
			return (false);
		}
		data->cmd_args[i] = *args;
		i++;
	}
	data->cmd_args[i] = NULL;
	return (true);
}

/*
 * Parses the command line, processing special characters and expanding paths.
 * Initializes cmd_paths in the data structure with full command paths.
 * Uses the provided environment variables for path resolution.
 * Returns true if parsing is successful, false otherwise.
*/
bool	parse_cmd_line(t_data *data, char **envp)
{
	int		i;
	int		new_index;
	char	**cmd;
	char	*path;

	i = 0;
	new_index = 0;
	if (!init_path(data))
		return (false);
	while (i < data->tok_num)
	{
		if (check_specials(data->token[i]))
			token_cleaner(data, i);
		cmd = ft_split(data->token[i], ' ');
		if (!cmd)
		{
			free_line(data->cmd_paths, data->tok_num);
			data->cmd_paths = NULL;
			return (false);
		}
		path = get_path(cmd[0], envp);
		data->cmd_paths[i] = path;
		free_line(cmd, -1);
		new_index++;
		i++;
	}
	return (true);
}

/*
 * Initializes the cmd_paths array in the data structure.
 * Allocates memory for storing command paths based on the number of tokens.
 * Returns true if initialization is successful, false if memory allocation fails.
*/
static inline bool	init_path(t_data *data)
{
	data->cmd_paths = ft_calloc(data->tok_num - 1, sizeof(char *));
	if (!data->cmd_paths)
		return (false);
	return (true);
}
