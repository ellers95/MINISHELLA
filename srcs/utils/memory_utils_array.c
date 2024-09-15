/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:23:04 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 19:04:07 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char ***paths, int arc);
char	*free_char_array(char **array);
void	free_stuff(char **args, char *path);
void	free_line(char **paths, int arc);

/*

*/
void	free_array(char ***paths, int arc)
{
	int	i;

	if (paths == NULL)
		return ;
	i = 0;
	if (arc == -1)
	{
		while (paths[i] != NULL)
		{
			free(*paths[i]);
			i++;
		}
	}
	else
	{
		while (i < arc)
		{
			if (*paths[i] != NULL)
				free((*paths[i]));
			i++;
		}
	}
	free (*paths);
	*paths = NULL;
}

/*

*/
char	*free_char_array(char **array)
{
	size_t	i;

	if (array == NULL)
		return (NULL);
	i = 0;
	while ((array)[i] != NULL)
	{
		free((array)[i]);
		(array)[i] = NULL;
		i++;
	}
	free(array);
	return (NULL);
}

/*

*/
void	free_stuff(char **args, char *path)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	if (path)
		free(path);
}

/*

*/
void	free_line(char **paths, int arc)
{
	int	i;

	if (paths == NULL)
		return ;
	i = 0;
	if (arc == -1)
	{
		while (paths[i] != NULL)
		{
			free(paths[i]);
			i++;
		}
	}
	else
	{
		while (i < arc)
		{
			if (paths[i] != NULL)
				free(paths[i]);
			i++;
		}
	}
	free(paths);
	paths = NULL;
}
