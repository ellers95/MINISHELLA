/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_configuration.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:06:03 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 00:12:23 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

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

*/
void	restore_terminal(const struct termios *original_termios)
{
	tcsetattr(STDIN_FILENO, TCSANOW, original_termios);
}
