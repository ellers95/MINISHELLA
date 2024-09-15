/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:43:50 by iniska            #+#    #+#             */
/*   Updated: 2024/09/16 00:21:28 by etaattol         ###   ########.fr       */
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
	char			*input;
	struct termios	original_termios;

	(void)argc;
	(void)argv;
	input = NULL;
	if (!ft_memset(&data, 0, sizeof(t_data)))
	{
		printf("Error: Memory setting error\n");
		exit (1);
	}
	data.last_exit_status = 0;
	load_list(&data, envp);
	setup_terminal(&original_termios);
	if (1)
	{
		signaling();
		while (1)
		{
			input = readline("✨🧚minishELLA🧚✨:");
			if (input == NULL)
			{
				write(1, "\n✨🧚 Adios 🧚✨!\n", 26);
				break ;
			}
			if (*input == '\0' || rl_end == 0)
			{
				free(input);
				continue ;
			}
			add_history(input);
			reset_struct(&data);
			if (!lexer(input, &data))
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
			free(input);
		}
		restore_terminal(&original_termios);
	}
	else
		printf("Error: Some error");
	clean_data(&data);
	return (0);
}
