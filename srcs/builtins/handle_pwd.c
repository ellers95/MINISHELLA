/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:46:52 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/14 23:41:27 by etaattol         ###   ########.fr       */
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
	char	*buf;

	token_cleaner(data, 0);
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		data->last_exit_status = 1;
		return (1);
	}
	printf("%s\n", buf);
	data->last_exit_status = 0;
	if (data->is_rdr)
		exit (0);
	return (0);
}
