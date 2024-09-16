/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:13:52 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/16 00:18:59 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Checks if a string contains only numeric characters.
 * Used to validate if a given argument is a valid number.
*/
int	number_checker(char *argv)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(argv) - 1)
	{
		if (ft_isdigit(argv[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
