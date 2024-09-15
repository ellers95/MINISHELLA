/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:05:06 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 18:36:28 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	load_list(t_data *data, char **envp);
t_node	*find_last(t_node	*stack);
t_node	*parse_str(t_node *node, char *str);
int		stack_len(t_node *stack);
void	remove_node(t_node *node);

/*

*/
void	load_list(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (add_end(&data->env, envp[i]))
		{
			free_env(&data->env);
			write(1, "Error\n", 6);
			exit(1);
		}
		i++;
	}
	return ;
}

/*

*/
t_node	*find_last(t_node	*stack)
{
	t_node	*temp;

	if (!stack)
		return (NULL);
	temp = stack;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

/*

*/
t_node	*parse_str(t_node *node, char *str)
{
	char	*split;
	int		i;

	i = 0;
	split = ft_strchr(str, '=');
	if (!split)
	{
		node->value = NULL;
		node->key = ft_strdup(str);
	}
	else
	{
		i = split - str;
		split++;
		node->value = ft_strdup(split);
		str[i] = '\0';
		node->key = ft_strdup(str);
	}
	return (node);
}

/*

*/
int	stack_len(t_node *stack)
{
	int	i;

	i = 0;
	if (!stack)
		return (0);
	while (stack)
	{
		stack = stack->next;
		i++;
	}
	return (i);
}

/*

*/
void	remove_node(t_node *node)
{
	t_node	*temp;

	if (!node->prev && !node->next)
	{
		(void)temp;
		free(node->key);
		free(node->value);
		free(node);
		return ;
	}
	else if (!node->prev && node->next)
	{
		temp = node->next;
		node->next = NULL;
		temp->prev = NULL;
		free(node->key);
		free(node->value);
		free(node);
		node = temp;
		return ;
	}
	else if (node->prev && !node->next)
	{
		temp = node->prev;
		temp->next = NULL;
		node->prev = NULL;
		free(node->key);
		free(node->value);
		free(node);
		node = temp;
		return ;
	}
	else
	{
		temp = node->prev;
		temp->next = node->next;
		temp->next->prev = temp;
		node->prev = NULL;
		node->next = NULL;
		free(node->key);
		free(node->value);
		free(node);
	}
}
