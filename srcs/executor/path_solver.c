/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_solver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:56:13 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/18 19:31:26 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Extracts the value of a specific environment variable.
*/
static inline char	*extract_env_value(char *env_value, char **envp)
{
	int	env_index;

	env_index = 0;
	while (envp && envp[env_index] != NULL)
	{
		if (ft_strncmp(env_value, envp[env_index], ft_strlen(env_value)) == 0
			&& envp[env_index][ft_strlen(env_value)] == '=')
			return (ft_strchr(envp[env_index], '=') + 1);
		env_index++;
	}
	return (NULL);
}

/*
* Finds and splits the PATH environment variable.
*/
static inline char	**find_path_directories(char **envp)
{
	char	*path_value;

	path_value = extract_env_value("PATH", envp);
	if (!path_value)
		return (NULL);
	return (ft_split(path_value, ':'));
}

/*
* Constructs and checks a full path for a command.
* Combines a directory path with a command name and checks if it exists.
*/
static inline char	*construct_and_check_path(char *directory, char *path_name)
{
	char	*path_with_slash;
	char	*full_command_path;

	path_with_slash = ft_strjoin(directory, "/");
	if (!path_with_slash)
		return (NULL);
	full_command_path = ft_strjoin(path_with_slash, path_name);
	ft_free(path_with_slash);
	if (!full_command_path)
		return (NULL);
	if (access(full_command_path, F_OK) == 0)
		return (full_command_path);
	ft_free(full_command_path);
	return (NULL);
}

/*
* Resolves the full path of a command.
* Searches for the command in the directories specified
* by the PATH environment variable. 
*/
char	*get_command_path(char *command_name, char **envp)
{
	int		path_index;
	char	*full_command_path;
	char	**path_directories;

	if (!command_name)
		return (NULL);
	if (access(command_name, F_OK) == 0)
		return (ft_substr(command_name, 0, ft_strlen(command_name)));
	path_directories = find_path_directories(envp);
	if (!path_directories)
		return (NULL);
	path_index = 0;
	while (path_directories[path_index] != NULL)
	{
		full_command_path = construct_and_check_path
			(path_directories[path_index], command_name);
		if (full_command_path)
		{
			free_line(path_directories, -1);
			return (full_command_path);
		}
		path_index++;
	}
	return (free_line(path_directories, -1), NULL);
}
