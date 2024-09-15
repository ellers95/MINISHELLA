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

char	*_getstatus(void);
char	get_heredoc_status(void);
void	set_heredoc_status(char status);

/*

*/
static inline char	*_getstatus(void)
{
	static char	status = 0;

	return (&status);
}

/*

*/
char	get_heredoc_status(void)
{
	return (*_getstatus());
}

/*

*/
void	set_heredoc_status(char status)
{
	*_getstatus() = status;
}
