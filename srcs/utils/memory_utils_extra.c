/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:04:48 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/16 00:14:08 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Frees a dynamically allocated array of strings (arguments).
 * Iterates through the array, freeing each string individually,
 * then frees the array itself.
*/
void	free_argh(char **argh)
{
	int	i;

	i = 0;
	while (argh[i])
	{
		free(argh[i]);
		i++;
	}
	free(argh);
}
