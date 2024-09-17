/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:46:37 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/17 17:38:52 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
static inline bool	init_command_paths(t_data *data)
{
	data->command_paths = ft_calloc(data->token_count, sizeof(char *));
	if (!data->command_paths)
		return (false);
	return (true);
}

static bool	process_command_token(t_data *data, char **envp,
			int i, int *new_index)
{
	char	**cmd;
	char	*path;
	
	cmd = ft_split(data->token[i], ' ');
	if (!cmd)
	{
		free_line(data->command_paths, data->token_count);
		data->command_paths = NULL;
		return (false);
	}
	path = get_command_path(cmd[0], envp);
	data->command_paths[*new_index] = path;
	(*new_index)++;
	free_line(cmd, -1);
	return (true);
}

/*
 * Parses the command line, processing special characters and expanding paths.
 * Initializes command_paths in the data structure with full command paths.
 * Uses the provided environment variables for path resolution.
 * Returns true if parsing is successful, false otherwise.
*/
bool	parse_command_line(t_data *data, char **envp)
{
	int		i;
	int		new_index;

	if (!init_command_paths(data))
		return (false);
	i = 0;
	new_index = 0;
	while (i < data->token_count)
	{
		if (is_special_shell_operator(data->token[i]))
			remove_token_and_shift_array(data, i);
		else
		{
			if (!process_command_token(data, envp, i, &new_index))
				return (false);
			i++;
		}
	}
	return (true);
}
