/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:46:37 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/16 11:35:01 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//bool	parse_command_arguments(t_data *data);
//bool	parse_cmd_line(t_data *data, char **envp);
//bool	init_path(t_data *data);

/*
 * Parses command arguments from the token array.
 * Allocates memory for and populates the command_arguments array 
 * in the data structure.
 * Returns true if parsing is successful, false otherwise.
*/
bool	parse_command_arguments(t_data *data)
{
	int		i;
	char	**args;

	data->command_arguments = ft_calloc(data->token_count, sizeof(char **));
	if (!data->command_arguments)
		return (false);
	i = 0;
	while (i < data->token_count - 1)
	{
		args = ft_split(data->token[i], ' ');
		if (!args)
		{
			free_array(&(data->command_arguments), i);
			data->command_arguments = NULL;
			return (false);
		}
		data->command_arguments[i] = *args;
		i++;
	}
	data->command_arguments[i] = NULL;
	return (true);
}

/*
 * Initializes the command_paths array in the data structure.
 * Allocates memory for storing command paths based on the number of tokens.
 * Returns true if initialization is successful, false if memory allocation fails.
*/
static inline bool	init_path(t_data *data)
{
	data->command_paths = ft_calloc(data->token_count, sizeof(char *));
	if (!data->command_paths)
		return (false);
	return (true);
}

/*
 * Parses the command line, processing special characters and expanding paths.
 * Initializes command_paths in the data structure with full command paths.
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
	while (i < data->token_count)
	{
		if (check_specials(data->token[i]))
			token_cleaner(data, i);
		cmd = ft_split(data->token[i], ' ');
		if (!cmd)
		{
			free_line(data->command_paths, data->token_count);
			data->command_paths = NULL;
			return (false);
		}
		path = get_command_path(cmd[0], envp);
		data->command_paths[i] = path;
		free_line(cmd, -1);
		new_index++;
		i++;
	}
	return (true);
}

