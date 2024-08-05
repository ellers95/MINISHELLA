/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:14:58 by iniska            #+#    #+#             */
/*   Updated: 2024/05/09 10:15:15 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static char	*extrct_path(char *path, char **envp)
{
	int	i;

	i = 0;
	while (envp[i++] != NULL)
	{
		if (ft_strncmp(path, envp[i], ft_strlen(path)) == 0
			&& envp[i][ft_strlen(path)] == '=')
			return (ft_strchr(envp[i], '=') + 1);
	}
	return (NULL);
}

static char	**find_path_env(char **envp)
{
	char	*path;

	path = extrct_path("PATH", envp);
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}

static char	*const_and_check(char *paths, char *path_name)
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

static char	*get_path(char *path_name, char **envp)
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

bool	parse_cmd_line(t_bananas *bana, char **envp)
{
    int		i;
    char	**cmd;
	char	*path;

    bana->cmd_paths = ft_calloc(bana->tok_num - 1, sizeof(char *));
    if (!bana->cmd_paths)
        return (false);

    i = 0;
    while (i < bana->tok_num)
    {
		//printf("Token before split: %s\n", bana->token[i]);
		
		if (check_specials(bana->token[i]))
		{
			i++;
			continue; // is this needed?!
		}

        cmd = ft_split(bana->token[i], ' ');
        if (!cmd)
        {
            free_line(bana->cmd_paths, bana->tok_num);
            bana->cmd_paths = NULL;
            return (false);
        }

		path = get_path(cmd[0], envp);
        bana->cmd_paths[i] = path;
        free_line(cmd, -1);
        i++;
    }

	//CHECKER!!

	//ft_printf("Command Paths:\n");
    //for (int j = 0; j < bana->tok_num; j++)
    //{
    //    if (bana->cmd_paths[j])
    //        ft_printf("Path %d: %s\n", j, bana->cmd_paths[j]);
    //    else
    //        ft_printf("EMPTYYYY Path %d: (NULL)\n", j);
    //}
	
	// CHECKER END!
    return (true);
}