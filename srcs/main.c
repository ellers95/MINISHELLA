/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:43:50 by iniska            #+#    #+#             */
/*   Updated: 2024/09/16 01:15:51 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * The main entry point for the minishell program.
 * Initializes the shell, sets up the environment,
 * and runs the main command loop.
*/
int	main(int argv, char **argc, char **envp)
{
	t_data			data;
	char			*user_input;
	struct termios	original_termios;

	(void)argc;
	(void)argv;
	user_input = NULL;
	if (!ft_memset(&data, 0, sizeof(t_data)))
	{
		printf("Error: Memory setting error\n");
		exit (1);
	}
	data.last_command_exit_status = 0;
	load_list(&data, envp);
	setup_terminal(&original_termios);
	if (1)
	{
		signaling();
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
			add_history(user_input);
			reset_struct(&data);
			if (!lexer(user_input, &data))
			{
				ft_printf("Lexer failed\n");
				break ;
			}
			if (!parser(&data))
				if (!data.env)
					free_env(&data.env);
			if (!execution(&data))
				printf("execution failed\n");
			if (data.heredoc_interrupted)
			{
				data.heredoc_interrupted = 0;
				continue ;
			}
			free(user_input);
		}
		restore_terminal(&original_termios);
	}
	else
		printf("Error: Some error");
	clean_data(&data);
	return (0);
}
