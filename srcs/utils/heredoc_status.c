/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:25:20 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/14 16:37:52 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_heredoc_status(void);
char	get_heredoc_status(void);
void	set_heredoc_status(char status);

/*
 * Internal function to manage the heredoc status.
 * Provides a static variable to store the current heredoc status.
*/
static inline char	*get_heredoc_status(void)
{
	static char	status = 0;

	return (&status);
}

/*
 * Retrieves the current status of heredoc processing.
*/
char	get_heredoc_status(void)
{
	return (*get_heredoc_status());
}

/*
 * Sets the status of heredoc processing.
 * Used to indicate whether the shell is currently handling a heredoc.
*/
void	set_heredoc_status(char status)
{
	*get_heredoc_status() = status;
}
