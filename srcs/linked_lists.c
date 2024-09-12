/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:29:28 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/12 15:00:51 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_node(t_node *node)
{
	t_node *temp;
	if (!node->prev && !node->next) //only node
	{
		(void)temp;
		free(node);
		return ;
	}
	else if (!node->prev && node->next) //first node
	{
		temp = node->next;
		node->next = NULL;
		temp->prev = NULL;
		free(node);
		node = temp;
		return ;
	}
	else if (node->prev && !node->next) //last node
	{
		temp = node->prev;
		temp->next = NULL;
		node->prev = NULL;
		free(node);
		node = temp;
		return ;
	}
	else
	//needs to handle for first node, last node, two nodes only, edges
	{
		temp = node->prev;
		temp->next = node->next;
		temp->next->prev = temp;
		node->prev = NULL;
		node->next = NULL;
		free(node);	
	}
}

t_node	*find_last(t_node	*stack)
{
	t_node	*temp;

	if (!stack)
		return (NULL);
	temp = stack;
	while (temp->next)
		temp = temp->next;
    // printf("inside find last\n");
	return (temp);
}

t_node   *parse_str(t_node *node, char *str)
{
    char *split;
    int i;

    i = 0;    
    split = ft_strchr(str, '=');
    // split++;
    if (!split)
    {
        ft_printf("no split\n");
        node->value = NULL;
        node->key = ft_strdup(str);
    }
    else
    {
        i = split - str;
        // ft_printf("i: %d\n", i);
        split++;
        node->value = ft_strdup(split);
        // ft_printf("value: %s\n", node->value);
        // free(split);
        str[i] = '\0';
        node->key = ft_strdup(str);
        // ft_strlcpy(node->key, str, i);
        // ft_printf("key: %s\n", node->key);
    }
    return (node);
}

void	free_env(t_node	**env)
{
	t_node	*temp;
	t_node	*curr;

   
	curr = *env;
	temp = NULL;
	while (curr)
	{
		temp = curr->next;
		free(curr);
		curr = temp;
	}
	*env = NULL;
}

void load_list(char **envp, t_node **env)
{
    int i;

    i = 0;
    // printf("Load_list\n");
    while (envp[i])
    {
        if (add_end(env, envp[i]))
        {
            free_env(env);
            write(1, "Error\n", 6);
            exit(1);
        }
        // printf("another line\n");
        i++;
    }
}

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