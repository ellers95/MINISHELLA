/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:47:35 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/16 13:31:01 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Implements the 'echo' builtin command.
* Prints the given arguments to the standard output.
* Supports the '-n' option to omit the trailing newline.
* Handles multiple arguments and preserves spaces between them.
*/
void	handle_echo(t_data *data)
{
	int		token_index;
	bool	suppress_newline;

	suppress_newline = false;
	token_index = 1;
	if (data->token_count == 1)
		printf("\n");
	else if (data->token_count > 1)
	{
		if (ft_strcmp(data->token[1], "-n") == 0)
		{
			remove_token_and_shift_array(data, 1);
			suppress_newline = true;
		}
		while (token_index <= data->token_count - 2)
			printf("%s ", data->token[token_index++]);
		if (data->token_count >= 2)
			printf("%s", data->token[data->token_count - 1]);
		if (suppress_newline == false)
			printf("\n");
	}
	while (data->token_count > 0)
		remove_token_and_shift_array(data, 0);
	if (data->has_redirection)
		exit (0);
}
