/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:48:56 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/16 22:50:57 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Implements the 'env' builtin command.
* Displays all environment variables that have both a key and a value.
* Each variable is printed in the format "key=value".
* Skips variables that have no assigned value.
*/
void	handle_env(t_data *data, t_node *env)
{
	(void)data;
	while (env->next)
	{
		if (!env)
			break ;
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	while (data->token_count > 0)
		remove_token_and_shift_array(data, 0);
	if (data->has_redirection)
		exit (0);
}
