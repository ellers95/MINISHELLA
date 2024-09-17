/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:05:09 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/17 18:58:06 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline t_node	*find_env_variable(char *key, t_node *env)
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

static char	*extract_variable_name(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != ' ' && str[i] != '\''
			&& str[i] != '"' && str[i] != '.'))
		i++;
	return (ft_substr(str, 1, i - 1));
}

static char	*handle_special_variable(const char *var_name, t_data *data)
{
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(data->last_command_exit_status));
	return (NULL);
}

static inline char	*expand_single_env_variable(char *str, t_node *env,
						t_data *data)
{
	char	*var_name;
	char	*expanded_value;
	t_node	*env_var;

	var_name = extract_variable_name(str);
	expanded_value = NULL;
	if (!var_name)
		return (str);
	env_var = find_env_variable(var_name, env);
	if (env_var && env_var->value)
		expanded_value = ft_strdup(env_var->value);
	else
		expanded_value = handle_special_variable(var_name, data);
	if (expanded_value)
	{
		if (ft_strlen(expanded_value) > ft_strlen(str))
			str = expanded_value;
		else
		{
			ft_strlcpy(str, expanded_value, ft_strlen(expanded_value) + 1);
			ft_free(expanded_value);
		}
	}
	ft_free(var_name);
	return (str);
}

/*
* Checks for and expands environment variables in a given string.
* Handles variable expansion within quotes and special cases like $?.
*/
char	*check_and_expand_env_variables(char *input_str, t_node *env,
			t_data *data)
{
	int		i;
	int		dollar_position;
	bool	single_quote;
	bool	double_quote;
	char	*dollar_ptr;

	i = 0;
	single_quote = false;
	double_quote = false;
	dollar_ptr = ft_strchr(input_str, '$');
	if (!dollar_ptr)
		return (input_str);
	dollar_position = dollar_ptr - input_str;
	while (input_str[i])
	{
		if (input_str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (input_str[i] == '"')
			double_quote = !double_quote;
		if (i == dollar_position && (!single_quote || (single_quote
					&& double_quote)))
			return (expand_single_env_variable(dollar_ptr, env, data));
		i++;
	}
	return (input_str);
}
