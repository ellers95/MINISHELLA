/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:37:22 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/17 15:16:38 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					add_end(t_node **stack, char *str);
char				**env_list_to_array(t_node **env);
static inline char	*create_env_string(t_node *node);

/*
 * Adds a new node to the end of the linked list (stack).
 * Parses the input string to create a new environment variable node.
 * If the list is empty, initializes it with the new node.
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
 * Converts the linked list of environment variables to an array of strings.
 * Each string in the array is in the format "KEY=VALUE".
 * This array format is typically used for execve() and similar functions.
*/
char	**env_list_to_array(t_node **env)
{
	int		len;
	int		i;
	t_node	*curr;
	char	**eepie;

	i = 0;
	curr = *env;
	len = stack_len(curr);
	eepie = ft_calloc(len, sizeof(char *));
	if (!eepie)
		return (NULL);
	while (i < len - 1 && curr)
	{
		eepie[i] = create_env_string(curr);
		if (!eepie[i])
		{
			free_char_array(eepie);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	return (eepie);
}

static inline char	*create_env_string(t_node *node)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(node->key, "=");
	if (!temp)
		return (NULL);
	if (node->value)
	{
		result = ft_strjoin(temp, node->value);
		free (temp);
		return (result);
	}
	else
		return (temp);
}
