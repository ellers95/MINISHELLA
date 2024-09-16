/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:30:47 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/16 12:23:55 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	call_builtin_function(t_data *data, char *command_name);

/*
* Handles execution of builtin commands.
* Checks if the current command is a builtin and executes it if so.
*/
void	builtins(t_data *data)
{
	size_t	command_length;
	char	*command_name;

	if (data->token[0])
	{
		command_name = data->token[0];
		command_length = ft_strlen(command_name);
		if (command_length > 0 && command_name[command_length - 1] == '\n')
			command_name[command_length - 1] = '\0';
		call_builtin_function(data, command_name);
		return ;
	}
}

/*
* Calls the appropriate function for a specific builtin command.
* This function is called by builtins() to execute the correct builtin.
*/
static inline void	call_builtin_function(t_data *data, char *command_name)
{
	if (ft_strcmp(command_name, "exit") == 0)
		handle_exit(data);
	else if (ft_strcmp(command_name, "pwd") == 0)
		handle_pwd(data);
	else if (ft_strcmp(command_name, "echo") == 0)
		handle_echo(data);
	else if (ft_strcmp(command_name, "unset") == 0)
		handle_unset(data, &data->env);
	else if (ft_strcmp(command_name, "env") == 0)
		handle_env(data, data->env);
	else if (ft_strcmp(command_name, "export") == 0)
		handle_export(data);
	else if (ft_strcmp(command_name, "cd") == 0)
		handle_cd(data, data->env);
	else
		return ;
}
