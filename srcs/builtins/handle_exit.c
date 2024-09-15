/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:56:50 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/15 16:22:25 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline size_t	exit_coder(char *argv);
static inline void	exiter(t_data *data);
void			handle_exit(t_data *data);

/*
* Converts a string argument to an exit code.
* Handles numeric input and ensures it's within the valid range (0-255).
*/
static size_t	exit_coder(char *argv)
{
	size_t			i;
	unsigned long	result;

	i = 0;
	result = 0;
	while (argv[i] != '\0')
	{
		if (!isdigit(argv[i]))
			return (0);
		i++;
	}
	i = 0;
	while (argv[i] != '\0')
	{
		if (result > (unsigned long)(INT_MAX / 10) ||
			(result == (unsigned long)(INT_MAX / 10) &&
				(argv[i] - '0') > (INT_MAX % 10)))
			result = result % ((unsigned long)INT_MAX + 1);
		result = result * 10 + (argv[i] - '0');
		i++;
	}
	return (result % 256);
}

/*
* Performs the actual exit process.
* Prints exit message, cleans up resources, and terminates the shell.
*/
static void	exiter(t_data *data)
{
	int	temp;
	{
		if (number_checker(data->token[1]))
		{
			temp = exit_coder(data->token[1]);
			ft_printf("Good bye!\nexit(%d)\n", temp);
			while (data->tok_num > 0)
				token_cleaner(data, 0);
			clean_data(data);
			exit(temp);
		}
		else
		{
			(void)temp;
			ft_printf("Good bye!\nexit\n%s: %s: count your 🍌s!\n",
				data->token[0], data->token[1]);
			while (data->tok_num > 0)
				token_cleaner(data, 2);
			clean_data(data);
			exit(0);
		}
	}
}

/*
* Implements the 'exit' builtin command.
* Parses arguments, determines the exit code, and calls exiter.
* Handles cases with and without arguments.
*/
void	handle_exit(t_data *data)
{
	if (data->tok_num == 1)
	{
		ft_printf("Good bye!\nexit\n");
		token_cleaner(data, 0);
		clean_data(data);
		exit(0);
	}
	else if (data->tok_num >= 2)
		exiter(data);
}
