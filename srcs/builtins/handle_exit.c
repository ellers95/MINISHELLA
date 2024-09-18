/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:56:50 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/18 17:06:33 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Converts a string argument to an exit code.
* Handles numeric input and ensures it's within the valid range (0-255).
*/
static size_t	exit_code_calculator(char *argv)
{
	size_t			char_index;
	unsigned long	result;

	char_index = 0;
	result = 0;
	while (argv[char_index] != '\0')
	{
		if (!ft_isdigit(argv[char_index]))
			return (0);
		char_index++;
	}
	char_index = 0;
	while (argv[char_index] != '\0')
	{
		if (result > (unsigned long)(INT_MAX / 10) ||
			(result == (unsigned long)(INT_MAX / 10) &&
				(argv[char_index] - '0') > (INT_MAX % 10)))
			result = result % ((unsigned long)INT_MAX + 1);
		result = result * 10 + (argv[char_index] - '0');
		char_index++;
	}
	return (result % 256);
}

/*
* Performs the actual exit process.
* Prints exit message, cleans up resources, and terminates the shell.
*/
static void	perform_exit(t_data *data)
{
	int		exit_code;
	bool	is_number;

	is_number = number_checker(data->token[1]);
	if (is_number)
	{
		exit_code = exit_code_calculator(data->token[1]);
		printf("Good bye!\nexit(%d)\n", exit_code);
		while (data->token_count > 0)
			remove_token_and_shift_array(data, 0);
	}
	else
	{
		printf("Good bye!\nexit\n%s: %s: count your 🍌s!\n",
			data->token[0], data->token[1]);
		while (data->token_count > 0)
			remove_token_and_shift_array(data, 2);
		exit_code = 0;
	}
	clean_data(data);
	exit(ft_clear(exit_code));
}

/*
* Implements the 'exit' builtin command.
* Parses arguments, determines the exit code, and calls perform_exit.
* Handles cases with and without arguments.
*/
void	handle_exit(t_data *data)
{
	if (data->token_count == 1)
	{
		printf("Good bye!\nexit\n");
		remove_token_and_shift_array(data, 0);
		clean_data(data);
		exit(ft_clear(0));
	}
	else if (data->token_count >= 2)
		perform_exit(data);
}
