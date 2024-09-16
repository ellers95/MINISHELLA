/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:14:58 by etaattol          #+#    #+#             */
/*   Updated: 2023/11/20 12:16:17 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int i)
{
	return ((i >= '0' && i <= '9') || (i >= 'a' && i <= 'z')
		|| (i >= 'A' && i <= 'Z'));
}