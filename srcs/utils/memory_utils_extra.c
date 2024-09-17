/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:04:48 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/17 18:58:06 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Frees a dynamically allocated array of strings (arguments).
 * Iterates through the array, freeing each string individually,
 * then frees the array itself.
*/
void	free_args(char **argh)
{
	int	i;

	i = 0;
	while (argh[i])
	{
		ft_free(argh[i]);
		i++;
	}
	ft_free(argh);
}
