/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:43:50 by iniska            #+#    #+#             */
/*   Updated: 2024/09/15 18:48:37 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

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
