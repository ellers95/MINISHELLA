/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:36:30 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/17 20:17:57 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline t_list	**_gethead(void);

void	ft_flist_add(t_list *newnode)
{
	t_list	*cur;
	t_list	*prv;

	cur = *_gethead();
	if (!cur)
		*_gethead() = newnode;
	else
	{
		while (cur)
		{
			prv = cur;
			cur = cur->next;
		}
		prv->next = newnode;
	}
}

void	ft_free(const void *blk)
{
	t_list	*cur;
	t_list	*prv;

	if (!blk)
		return ;
	cur = *_gethead();
	if (!cur)
		return ;
	prv = NULL;
	while (cur && cur->content != blk)
	{
		prv = cur;
		cur = cur->next;
	}
	if (cur)
	{
		if (!prv)
			*_gethead() = cur->next;
		else
			prv->next = cur->next;
		free(cur->content);
		free(cur);
	}
}

int	ft_clear(const int retval)
{
	t_list	*cur;
	t_list	*prv;

	cur = *_gethead();
	while (cur)
	{
		prv = cur;
		cur = cur->next;
		free(prv->content);
		free(prv);
	}
	*_gethead() = NULL;
	return ((int)retval);
}

static inline t_list	**_gethead(void)
{
	static t_list	*head = NULL;

	return (&head);
}
