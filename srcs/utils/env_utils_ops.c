/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:37:22 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 00:11:05 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		add_end(t_node **stack, char *str);
char	**list_to_eepie(t_node **env);

/*

*/
int	add_end(t_node **stack, char *str)
{
	t_node	*pre;
	t_node	*last;

	last = malloc(sizeof(t_node));
	if (!last)
		return (1);
	last->next = NULL;
	last = parse_str(last, str);
	if (!(*stack))
	{
		*stack = last;
		last->prev = NULL;
	}
	else
	{
		pre = find_last(*stack);
		pre->next = last;
		last->prev = pre;
	}
	return (0);
}

/*

*/
char	**list_to_eepie(t_node **env)
{
	int		len;
	int		i;
	t_node	*curr;
	char	*temp;
	char	**eepie;
	char	*temp_value;

	i = 0;
	curr = *env;
	len = stack_len(curr);
	eepie = ft_calloc(len, sizeof(char *));
	if (!eepie)
		return (NULL);
	while (i < len - 1)
	{
		if (curr->key)
		{
			temp = ft_strjoin(curr->key, "=");
			if (temp)
			{
				if (curr->value)
				{
					temp_value = ft_strjoin(temp, curr->value);
					free(temp);
					if (temp_value)
					{
						eepie[i] = ft_strdup(temp_value);
						free(temp_value);
					}
				}
				else
					eepie[i] = ft_strdup(temp);
			}
		}
		curr = curr->next;
		i++;
	}
	return (eepie);
}