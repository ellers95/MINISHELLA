/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:43:50 by iniska            #+#    #+#             */
/*   Updated: 2024/09/19 08:07:57 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Sets up the initial shell environment
*/
static inline void	initialize_shell(t_data *data, char **envp,
	struct termios *original_termios)
{
	if (!ft_memset(data, 0, sizeof(t_data)))
	{
		printf("Error: Memory setting error\n");
		exit (1);
	}
	data->last_command_exit_status = 0;
	load_list(data, envp);
	setup_terminal(original_termios);
	signaling();
}

/*
* Handles lexing, parsing, and execution of user commands
*/
static inline void	process_input(t_data *data, char *user_input)
{
	add_history(user_input);
	reset_struct(data);
	if (!lexer(user_input, data) || !parser(data) || !execution(data))
	{
		if (!data->env)
			free_env(&data->env);
		printf("Error: Command processing failed\n");
	}
	free(user_input);
}

/*
* Implements the main command loop
*/
static inline void	run_shell(t_data *data)
{
	char	*user_input;

	while (1)
	{
		user_input = readline("✨🧚minishELLA🧚✨:");
		if (user_input == NULL)
		{
			write(1, "\n✨🧚 Adios 🧚✨!\n", 24);
			break ;
		}
		if (*user_input == '\0' || rl_end == 0)
		{
			free(user_input);
			continue ;
		}
		process_input(data, user_input);
		if (data->heredoc_interrupted)
		{
			data->heredoc_interrupted = 0;
			continue ;
		}
	}
}
/*
 * This file contains the main entry point
 * and core logic for the minishell program.
 * It initializes the shell environment,
 * sets up signal handling and terminal settings,
 * and implements the main command loop for
 * reading and processing user input.
*/
int	main(int argv, char **argc, char **envp)
{
	t_data			data;
	struct termios	original_termios;

	(void)argc;
	(void)argv;
	initialize_shell(&data, envp, &original_termios);
	run_shell(&data);
	clean_data(&data);
	restore_terminal(&original_termios);
	return (ft_clear(0));
}
