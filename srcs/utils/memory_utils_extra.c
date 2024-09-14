/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:04:48 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 00:11:50 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

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
