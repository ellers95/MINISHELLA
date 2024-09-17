/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:31:35 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/17 18:58:28 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_alloc(const size_t n)
{
	t_list	*node;

	if (!n)
		return (NULL);
	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	*node = (t_list){.content = malloc(n), .next = NULL};
	if (!node->content)
	{
		ft_free(node);
		return (NULL);
	}
	ft_flist_add(node);
	return (node->content);
}