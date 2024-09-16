/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:56:50 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/16 23:12:27 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline size_t	exit_code_calculator(char *argv);
static inline void	perform_exit(t_data *data);

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
	int	exit_code;
	{
		if (number_checker(data->token[1]))
		{
			exit_code = exit_code_calculator(data->token[1]);
			ft_printf("Good bye!\nexit(%d)\n", exit_code);
			while (data->token_count > 0)
				remove_token_and_shift_array(data, 0);
			clean_data(data);
			exit(exit_code);
		}
		else
		{
			(void)exit_code;
			ft_printf("Good bye!\nexit\n%s: %s: count your 🍌s!\n",
				data->token[0], data->token[1]);
			while (data->token_count > 0)
				remove_token_and_shift_array(data, 2);
			clean_data(data);
			exit(0);
		}
	}
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
		ft_printf("Good bye!\nexit\n");
		remove_token_and_shift_array(data, 0);
		clean_data(data);
		exit(0);
	}
	else if (data->token_count >= 2)
		perform_exit(data);
}
