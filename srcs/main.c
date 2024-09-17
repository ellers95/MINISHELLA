/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:43:50 by iniska            #+#    #+#             */
/*   Updated: 2024/09/17 15:44:03 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * The main entry point for the minishell program.
 * Initializes the shell, sets up the environment,
 * and runs the main command loop.
*/
static inline void	initialize_shell(t_data *data, char **envp, struct termios *original_termios)
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

static inline void	run_shell(t_data *data)
{
	char	*user_input;
	while (1)
	{
		user_input = readline("✨🧚minishELLA🧚✨:");
		if (user_input == NULL)
		{
			write(1, "\n✨🧚 Adios 🧚✨!\n", 26);
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

	return (0);
}
