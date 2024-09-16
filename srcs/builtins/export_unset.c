/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:01:53 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/16 12:10:00 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void			handle_export(t_data *data);
//void			handle_unset(t_data *data, t_node **env);
static inline void	handle_export_no_args(t_data *data, t_node *env);
static inline void	add_to_env(t_data *data, t_node *env, char *value_start, int key_length);
static inline void	search_env(t_data *data, t_node *env, char *value_start, int key_length);

/*
* Handles the 'export' builtin command.
* Adds or modifies environment variables based on the provided arguments.
* If called without arguments, it displays all environment variables.
*/
void	handle_export(t_data *data)
{
	char	*value_start;
	int		key_length;

	value_start = NULL;
	if (data->token_count == 1)
		handle_export_no_args(data, data->env);
	while (data->token_count >= 1)
	{
		if (!ft_strcmp(data->token[0], "export"))
			token_cleaner(data, 0);
		if (ft_strchr(data->token[0], '='))
		{
			value_start = ft_strchr(data->token[0], '=');
			value_start++;
			key_length = value_start - data->token[0] - 1;
		}
		else
			key_length = ft_strlen(data->token[0]);
		search_env(data, data->env, value_start, key_length);
		token_cleaner(data, 0);
		value_start = NULL;
	}
	if (data->has_redirection)
		exit (0);
}

/*
* Handles the 'unset' builtin command.
* Removes specified variables from the environment.
*/
void	handle_unset(t_data *data, t_node **env)
{
	t_node	*current_node;

	current_node = NULL;
	token_cleaner(data, 0);
	while (data->token_count >= 1)
	{
		current_node = *env;
		while (current_node->next)
		{
			if (!ft_strcmp(current_node->key, data->token[0]))
			{
				printf("key = %s\n", current_node->key);
				token_cleaner(data, 0);
				free(current_node->key);
				free(current_node->value);
				current_node->key = NULL;
				current_node->value = NULL;
				remove_node(current_node);
				break ;
			}
			current_node = current_node->next;
		}
	}
	if (data->has_redirection)
		exit (0);
}

/*
* Handles 'export' when called without arguments.
* Displays all environment variables in the required format.
*/
static inline void	handle_export_no_args(t_data *data, t_node *env)
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
static inline void	add_to_env(t_data *data, t_node *env, char *value_start, int key_length)
{
	add_end(&env, data->token[0]);
	if (value_start)
	{
		ft_strlcpy(env->key, data->token[0], key_length + 1);
		env->value = ft_strdup(value_start);
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
static inline void	search_env(t_data *data, t_node *env, char *value_start, int key_length)
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
			if (value_start)
				env->value = ft_strdup(value_start);
		}
		env = env->next;
	}
	if (found_in_env == false)
		add_to_env(data, env, value_start, key_length);
	while (env->prev)
		env = env->prev;
}
