/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:46:52 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/17 19:18:11 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Implements the 'pwd' (print working directory) builtin command.
* Prints the current working directory to the standard output.
* Uses the getcwd() function to retrieve the current directory.
*/
int	handle_pwd(t_data *data)
{
	char	*current_directory;

	remove_token_and_shift_array(data, 0);
	current_directory = getcwd(NULL, 0);
	if (!current_directory)
	{
		data->last_command_exit_status = 1;
		return (1);
	}
	printf("%s\n", current_directory);
	free(current_directory);
	data->last_command_exit_status = 0;
	if (data->has_redirection)
		exit (0);
	return (0);
}
