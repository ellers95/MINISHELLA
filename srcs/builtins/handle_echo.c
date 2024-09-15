/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:47:35 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 17:16:38 by etaattol         ###   ########.fr       */
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
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 1;
	if (data->tok_num == 1)
		printf("\n");
	else if (data->tok_num > 1)
	{
		if (ft_strcmp(data->token[1], "-n") == 0)
		{
			token_cleaner(data, 1);
			n_flag = true;
		}
		while (i <= data->tok_num - 2)
			printf("%s ", data->token[i++]);
		if (data->tok_num >= 2)
			printf("%s", data->token[data->tok_num - 1]);
		if (n_flag == false)
			printf("\n");
	}
	while (data->tok_num > 0)
		token_cleaner(data, 0);
	if (data->is_rdr)
		exit (0);
}
