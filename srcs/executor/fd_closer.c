/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_closer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:06:23 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 23:52:41 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Closes both ends of a pipe.
 * This function is typically used to clean up file descriptors
 * after forking or when a pipe is no longer needed.
 * It ensures that both the read (fd[0]) and write (fd[1])
 *  ends of the pipe are closed.
*/
void	shut_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}
