/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:10:17 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/12 15:04:57 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	lone_export(t_bananas *bana, t_node *env)
{
	while (env->next)
	{
		if (!env)
			break ;
		else if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else if (!env->value)
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
	token_cleaner(bana, 0);
}

static void	add_to_env(t_bananas *bana, t_node *env, char *temp, int len)
{
	add_end(&env, "");
	if (temp)
	{
		ft_strlcpy(env->key, bana->token[0], len + 1);
		env->value = ft_strdup(temp);
	}
	else
	{
		env->key = ft_strdup(bana->token[0]);
		env->value = NULL;
	}
}

static void	search_env(t_bananas *bana, t_node *env, char *temp, int len)
{
	bool	found_in_env;

	found_in_env = false;
	while (env->next)
	{
		if (!env)
			break ;
		else if (!ft_strcmp(env->key, bana->token[0]))
		{
			found_in_env = true;
			if (temp)
				env->value = ft_strdup(temp);
		}
		env = env->next;
	}
	if (found_in_env == false)
		add_to_env(bana, env, temp, len);
	while (env->prev)
		env = env->prev;
}

void	handle_export(t_bananas *bana, t_node *env)
{
	char	*temp;
	int		len;

	temp = NULL;
	if (bana->tok_num == 1)
		lone_export(bana, env);
	while (bana->tok_num >= 1)
	{
		if (!ft_strcmp(bana->token[0], "export"))
			token_cleaner(bana, 0);
		if (ft_strchr(bana->token[0], '='))
		{
			temp = ft_strchr(bana->token[0], '=');
			temp++;
			len = temp - bana->token[0] - 1;
		}
		else
			len = ft_strlen(bana->token[0]);
		search_env(bana, env, temp, len);
		token_cleaner(bana, 0);
		temp = NULL;
	}
	if (bana->is_rdr)
		exit (0);
}

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