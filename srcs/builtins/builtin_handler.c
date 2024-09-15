/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:30:47 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 17:11:40 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			builtins(t_data *data);
static inline void	call_builtin_function(t_data *data, char *bi);

/*
* Handles execution of builtin commands.
* Checks if the current command is a builtin and executes it if so.
*/
void	builtins(t_data *data)
{
	size_t	len;
	char	*bi;

	if (data->token[0])
	{
		bi = data->token[0];
		len = ft_strlen(bi);
		if (len > 0 && bi[len - 1] == '\n')
			bi[len - 1] = '\0';
		call_builtin_function(data, bi);
		return ;
	}
}

/*
* Calls the appropriate function for a specific builtin command.
* This function is called by builtins() to execute the correct builtin.
*/
static inline void	call_builtin_function(t_data *data, char *bi)
{
	if (ft_strcmp(bi, "exit") == 0)
		handle_exit(data);
	else if (ft_strcmp(bi, "pwd") == 0)
		handle_pwd(data);
	else if (ft_strcmp(bi, "echo") == 0)
		handle_echo(data);
	else if (ft_strcmp(bi, "unset") == 0)
		handle_unset(data, &data->env);
	else if (ft_strcmp(bi, "env") == 0)
		handle_env(data, data->env);
	else if (ft_strcmp(bi, "export") == 0)
		handle_export(data);
	else if (ft_strcmp(bi, "cd") == 0)
		handle_cd(data, data->env);
	else
		return ;
}
