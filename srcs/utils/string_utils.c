/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:13:52 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 00:12:16 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

*/
int	number_checker(char *argv)
{
	size_t i;

	i = 0;
	while (i <= ft_strlen(argv) - 1)
	{
		if (ft_isdigit(argv[i]) == 1)
			return (1);
		i++;	
	}
	return (0);
}
