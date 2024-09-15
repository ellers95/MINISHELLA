/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_configuration.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:06:03 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/16 00:20:41 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_terminal(struct termios *original_termios);
void	restore_terminal(const struct termios *original_termios);

/*
 * Sets up the terminal for custom input handling.
 * Disables the echoing of control characters (like ^C) to the terminal.
 * Saves the original terminal settings and applies modified settings.
*/
void	setup_terminal(struct termios *original_termios)
{
	struct termios	new_termios;

	tcgetattr(STDIN_FILENO, original_termios);
	new_termios = *original_termios;
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

/*
 * Restores the terminal to its original settings.
*/
void	restore_terminal(const struct termios *original_termios)
{
	tcsetattr(STDIN_FILENO, TCSANOW, original_termios);
}
