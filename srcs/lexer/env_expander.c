/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:05:09 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/15 19:07:51 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_variable_check(char *str, t_node *env, t_data *data);
t_node	*find_key(char *key, t_node *env);
char	*expand_var(char *str, t_node *env, t_data *data);

/*
* Checks for and expands environment variables in a given string.
* Handles variable expansion within quotes and special cases like $?.
*/
char	*env_variable_check(char *str, t_node *env, t_data *data)
{
	int		i;
	int		single_quote;
	int		double_quote;
	char	*dollar_ptr;
	int		dollar_pos;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	dollar_ptr = ft_strchr(str, '$');
	if (!dollar_ptr)
		return (str);
	dollar_pos = dollar_ptr - str;
	while (str[i])
	{
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (str[i] == '"')
			double_quote = !double_quote;
		if (i == dollar_pos)
		{
			if (!single_quote || (single_quote && double_quote))
			{
				str = expand_var(dollar_ptr, env, data);
				return (str);
			}
			else
				return (str);
		}
		i++;
	}
	return (str);
}

/*
* Searches for a specific key in the environment variable linked list.
*/
static inline t_node	*find_key(char *key, t_node *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		else
			env = env->next;
	}
	return (NULL);
}

/*
* Expands a single environment variable.
* Handles special cases like $? for last exit status.
*/
static inline char	*expand_var(char *str, t_node *env, t_data *data)
{
	t_node	*temp_node;
	char	*var_name;
	int		i;
	int		j;
	size_t	value_len;
	char	*temp_str;

	value_len = 0;
	i = 1;
	while (str[i] && (str[i] != ' ' && str[i] != '\0'
			&& str[i] != '\'' && str[i] != '"' && str[i] != '.'))
		i++;
	var_name = ft_calloc(i + 1, sizeof(char));
	if (!var_name)
		return (str);
	j = 1;
	while (j < i)
	{
		var_name[j - 1] = str[j];
		j++;
	}	
	var_name[j - 1] = '\0';
	temp_node = find_key(var_name, env);
	if (temp_node && temp_node->value)
	{
		value_len = ft_strlen(temp_node->value);
		if (value_len <= ft_strlen(str))
			ft_strlcpy(str, temp_node->value, value_len + 1);
		else
		{
			temp_str = ft_strdup(temp_node->value);
			str = temp_str;
		}
	}
	else if (ft_strcmp(var_name, "?") == 0)
	{
		temp_str = ft_itoa(data->last_exit_status);
		value_len = ft_strlen(temp_str);
		if (value_len <= ft_strlen(str))
			ft_strlcpy(str, temp_str, value_len + 1);
		else
		{
			if (temp_str)
			{
				free (str);
				str = temp_str;
			}
		}
	}
	else
		printf("Variable not found or has no value: %s\n", var_name);
	free(var_name);
	return (str);
}
