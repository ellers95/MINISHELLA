/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:17:48 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 19:00:22 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signaling(void);
void	handle_sigint(int sig);
void	handle_quit(int sig);
int		big_stopping(int get, int newvalue);

/*

*/
void	signaling(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = handle_quit;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/*

*/
static inline void	handle_sigint(int sig)
{
	(void)sig;
	if (get_heredoc_status() == IN_HEREDOC)
	{
		write(STDOUT_FILENO, "^C\n", 3);
		rl_done = 1;
		close(STDIN_FILENO);
		big_stopping(SET, 1);
	}
	else
	{
		write(STDOUT_FILENO, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*

*/
static inline void	handle_quit(int sig)
{
	(void)sig;
}

/*

*/

/*

*/
int	big_stopping(int get, int newvalue)
{
	static int	stopper = 0;

	if (get)
		return (stopper);
	else
		stopper = newvalue;
	return (stopper);
}
