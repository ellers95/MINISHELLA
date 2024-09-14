/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_solver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:56:13 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/14 23:45:51 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*get_path(char *path_name, char **envp);
static inline char	**find_path_env(char **envp);
static inline char	*extract_path(char *path, char **envp);
static inline char	*const_and_check(char *paths, char *path_name);

/*
* Resolves the full path of a command.
* Searches for the command in the directories specified by the PATH environment variable. 
*/
char	*get_path(char *path_name, char **envp)
{
	int		i;
	char	*full_path;
	char	**paths;

	if (access(path_name, F_OK) == 0)
		return (ft_substr(path_name, 0, ft_strlen(path_name)));
	paths = find_path_env(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		full_path = const_and_check(paths[i], path_name);
		if (full_path)
		{
			free_line(paths, -1);
			return (full_path);
		}
		i++;
	}
	return (free_line(paths, -1), NULL);
}

/*
* Finds and splits the PATH environment variable.
*/
static inline char	**find_path_env(char **envp)
{
	char	*path;

	path = extract_path("PATH", envp);
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}

/*
* Extracts the value of a specific environment variable.
*/
static inline char	*extract_path(char *path, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(path, envp[i], ft_strlen(path)) == 0
			&& envp[i][ft_strlen(path)] == '=')
			return (ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (NULL);
}

/*
* Constructs and checks a full path for a command.
* Combines a directory path with a command name and checks if it exists.
*/
static inline char	*const_and_check(char *paths, char *path_name)
{
	char	*oneline;
	char	*full_path;

	oneline = ft_strjoin(paths, "/");
	if (!oneline)
		return (NULL);
	full_path = ft_strjoin(oneline, path_name);
	free(oneline);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}
