/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:11:50 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/14 23:39:33 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Implements the 'cd' (change directory) builtin command.
* Changes the current working directory of the shell.
* If no argument is provided, it changes to the home directory.
*/
void handle_cd(t_data *data, t_node *env)
{
    (void)env;
    token_cleaner(data, 0);
    if(chdir(data->token[0]))
        printf("cd: %s not set\n", data->token[0]);
    if (data->token[0])
        token_cleaner(data, 0);
}