/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:11:50 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/18 20:40:37 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Updates the OLDPWD environment variable with the provided old_pwd value.
* Searches for OLDPWD in the environment list and replaces its value.
*/
static inline void	old_pwd_update(t_node *env, char *old_pwd)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "OLDPWD"))
		{
			ft_free(env->value);
			env->value = ft_strdup(old_pwd);
			break ;
		}
		env = env->next;
	}
}

/*
* Updates the PWD environment variable witt the current working directory.
* Returns the old PWD value or NULL on failure.
*/
static char	*new_pwd_update(t_node *env, t_data *data)
{
	static char	buf[2048];
	char		*old_pwd;

	old_pwd = NULL;
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
		{
			old_pwd = ft_strdup(env->value);
			ft_free(env->value);
			getcwd(buf, 0);
			env->value = ft_strdup(buf);
			if (!env->value)
			{
				data->last_command_exit_status = 1;
				perror("getcwd failed in update_pwds");
				ft_free(old_pwd);
				return (NULL);
			}
			break ;
		}
		env = env->next;
	}
	return (old_pwd);
}

/*
* Updates PWD and OLDPWD environment variables after a directory change.
* PWD is set to the current working directory, OLDPWD to the previous PWD.
*/
void	update_pwds(t_data *data)
{
	char	*old_pwd;
	t_node	*env;

	env = data->env;
	old_pwd = new_pwd_update(env, data);
	if (old_pwd)
	{
		old_pwd_update(env, old_pwd);
		ft_free(old_pwd);
	}
}

/*
* Changes the current directory to the user's home directory.
* Updates PWD if successful, sets error status and prints message if not.
*/
void	homeward_bound(t_data *data)
{
	char	*home;

	home = msh_getenv("HOME", data->env);
	if (home)
	{
		if (chdir(home) != 0)
		{
			data->last_command_exit_status = 1;
			perror("cd: Failed to change to home directory");
		}
		else
			update_pwds(data);
	}
	else
	{
		data->last_command_exit_status = 1;
		printf("Error: cd: HOME not set\n");
	}
}

/*
* Handles the 'cd' (change directory) command.
* Changes to home directory if no argument or '~' is given.
* Otherwise, changes to the specified directory.
* Updates PWD and OLDPWD on success, sets error status on failure.
*/
void	handle_cd(t_data *data)
{
	if (data->token_count <= 2)
	{
		remove_token_and_shift_array(data, 0);
		if (!data->token || !data->token[0]
			|| (!ft_strcmp(data->token[0], "~")))
		{
			homeward_bound(data);
			update_pwds(data);
			while (data->token_count > 0)
				remove_token_and_shift_array(data, 0);
			return ;
		}
		if (chdir(data->token[0]))
		{
			printf("cd: %s not set\n", data->token[0]);
			return ;
		}
		update_pwds(data);
	}
	while (data->token_count > 0)
		remove_token_and_shift_array(data, 0);
	if (data->has_redirection)
		exit (0);
}
