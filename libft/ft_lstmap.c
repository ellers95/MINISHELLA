/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:56:38 by etaattol          #+#    #+#             */
/*   Updated: 2024/02/16 15:09:16 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst2;
	t_list	*new;
	void	*new_content;

	if (!lst)
		return (0);
	lst2 = 0;
	while (lst)
	{
		new_content = f(lst->content);
		new = ft_lstnew(new_content);
		if (!new)
		{
			if (del)
				del(new_content);
			ft_lstclear(&lst2, del);
			return (0);
		}
		ft_lstadd_back(&lst2, new);
		lst = lst->next;
	}
	return (lst2);
}
