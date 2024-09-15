/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:01:53 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/15 16:22:49 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			handle_export(t_data *data);
void			handle_unset(t_data *data, t_node **env);
static inline void	lone_export(t_data *data, t_node *env);
static inline void	add_to_env(t_data *data, t_node *env, char *temp, int len);
static inline void	search_env(t_data *data, t_node *env, char *temp, int len);

/*
* Handles the 'export' builtin command.
* Adds or modifies environment variables based on the provided arguments.
* If called without arguments, it displays all environment variables.
*/
void	handle_export(t_data *data)
{
	char	*temp;
	int		len;

	temp = NULL;
	if (data->tok_num == 1)
		lone_export(data, data->env);
	while (data->tok_num >= 1)
	{
		if (!ft_strcmp(data->token[0], "export"))
			token_cleaner(data, 0);
		if (ft_strchr(data->token[0], '='))
		{
			temp = ft_strchr(data->token[0], '=');
			temp++;
			len = temp - data->token[0] - 1;
		}
		else
			len = ft_strlen(data->token[0]);
		search_env(data, data->env, temp, len);
		token_cleaner(data, 0);
		temp = NULL;
	}
	if (data->is_rdr)
		exit (0);
}

/*
* Handles the 'unset' builtin command.
* Removes specified variables from the environment.
*/
void	handle_unset(t_data *data, t_node **env)
{
	t_node	*node;

	node = NULL;
	token_cleaner(data, 0);
	while (data->tok_num >= 1)
	{
		node = *env;
		while (node->next)
		{
			if (!ft_strcmp(node->key, data->token[0]))
			{
				printf("key = %s\n", node->key);
				token_cleaner(data, 0);
				free(node->key);
				free(node->value);
				node->key = NULL;
				node->value = NULL;
				remove_node(node);
				break ;
			}
			node = node->next;
		}
	}
	if (data->is_rdr)
		exit (0);
}

/*
* Handles 'export' when called without arguments.
* Displays all environment variables in the required format.
*/
static inline void	lone_export(t_data *data, t_node *env)
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
	token_cleaner(data, 0);
}

/*
* Adds a new variable to the environment.
* Used by handle_export when a new variable needs to be added.
*/
static inline void	add_to_env(t_data *data, t_node *env, char *temp, int len)
{
	add_end(&env, data->token[0]);
	if (temp)
	{
		ft_strlcpy(env->key, data->token[0], len + 1);
		env->value = ft_strdup(temp);
	}
	else
	{
		env->key = ft_strdup(data->token[0]);
		env->value = NULL;
	}
}

/*
* Searches for an existing variable in the environment and updates it.
* Used by handle_export to update existing variables
*/
static inline void	search_env(t_data *data, t_node *env, char *temp, int len)
{
	bool	found_in_env;

	found_in_env = false;
	while (env->next)
	{
		if (!env)
			break ;
		else if (!ft_strcmp(env->key, data->token[0]))
		{
			found_in_env = true;
			if (temp)
				env->value = ft_strdup(temp);
		}
		env = env->next;
	}
	if (found_in_env == false)
		add_to_env(data, env, temp, len);
	while (env->prev)
		env = env->prev;
}
