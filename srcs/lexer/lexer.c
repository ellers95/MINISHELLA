/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:32:34 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/18 11:18:53 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	remove_quotes_from_token(char *token)
{
	int		char_index;
	size_t	len;
	char	quote;

	char_index = 0;
	len = ft_strlen(token);
	while (token[char_index])
	{
		if (token[char_index] == '\'' || token[char_index] == '"')
		{
			quote = token[char_index];
			ft_memmove(token + char_index, token + char_index + 1,
				len-- - char_index);
			while (token[char_index] && token[char_index] != quote)
				char_index++;
			if (token[char_index] == quote)
			{
				ft_memmove(token + char_index, token + char_index + 1,
					len-- - char_index);
			}
		}
		else
			char_index++;
	}
}

/*
* Removes quotes from tokens.
* Handles both single and double quotes, preserving content between them.
*/
static inline void	delete_quotes(t_data *data)
{
	int		token_index;

	token_index = 0;
	while (data->token[token_index])
	{
		remove_quotes_from_token(data->token[token_index]);
		token_index++;
	}
}

static inline int	handle_token_content(char *input_str, int i, char *current_quote)
{
	int	quotes;

	quotes = 0;
	while (input_str[i] && (!is_whitespace(input_str[i]) || quotes))
	{
		if (input_str[i] == '"' || input_str[i] == '\'')
		{
			if (quotes && input_str[i] == *current_quote)
			{
				quotes = 0;
				*current_quote = 0;
			}
			else if (!quotes)
			{
				quotes = 1;
				*current_quote = input_str[i];
			}
		}
		i++;
	}
	return (i);
}

static bool	process_token(t_data *data, char *input_str, int *char_index,
			char *current_quote)
{
	int	start;

	start = *char_index;
	*char_index = handle_token_content(input_str, *char_index, current_quote);
	data->token[data->lexer_token_index] = ft_calloc(*char_index - start + 1, sizeof(char));
	if (!data->token[data->lexer_token_index])
		return (false);
	ft_strlcpy(data->token[data->lexer_token_index], &input_str[start],
		*char_index - start + 1);
	data->token[data->lexer_token_index] = check_and_expand_env_variables
		(data->token[data->lexer_token_index], data->env, data);
	return (true);
}

/*
* Main lexical analysis function.
* Tokenizes the input string and handles quotes and environment variables.
*/
bool	lexer(char *input_str, t_data *data)
{
	int		char_index;
	char	current_quote;

	char_index = 0;
	current_quote = 0;
	data->lexer_token_index = 0;
	data->token_count = count_tokens(input_str);
	data->token = ft_calloc((data->token_count + 1), sizeof(char *));
	if (!data->token)
		return (false);
	while (data->lexer_token_index < data->token_count && input_str[char_index])
	{
		while (input_str[char_index] && is_whitespace(input_str[char_index]))
			char_index++;
		if (input_str[char_index])
		{
			if (!process_token(data, input_str, &char_index, &current_quote))
				return (false);
			data->lexer_token_index++;
		}
	}
	delete_quotes(data);
	return (true);
}
