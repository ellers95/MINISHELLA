/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:32:34 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/16 13:26:02 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	count_tokens(char *input_str);
static inline void	delete_quotes(t_data *data);
static inline int	handle_quote(char *input_str, char *current_quote, int i);
static inline int	is_whitespace(char c);

/*
* Main lexical analysis function.
* Tokenizes the input string and handles quotes and environment variables.
*/
bool	lexer(char *input_str, t_data *data)
{
	int		char_index;
	int		token_index;
	char	current_quote;
	int		start;

	char_index = 0;
	token_index = 0;
	current_quote = 0;
	data->token_count = count_tokens(input_str);
	data->token = ft_calloc((data->token_count + 1), sizeof(char *));
	if (!data->token)
		return (false);
	while (token_index < data->token_count && input_str[char_index])
	{
		while (input_str[char_index] && is_whitespace(input_str[char_index]))
			char_index++;
		if (input_str[char_index])
		{
			start = char_index;
			char_index = handle_quote(input_str, &current_quote, char_index);
			data->token[token_index] = ft_calloc(char_index - start + 1, sizeof(char));
			if (!data->token[token_index])
				return (false);
			ft_strlcpy(data->token[token_index], &input_str[start], char_index - start + 1);
			data->token[token_index] = check_and_expand_env_variables
				(data->token[token_index], data->env, data);
			token_index++;
		}
	}
	delete_quotes(data);
	return (true);
}

/*
* Counts the number of tokens in the input string.
* Considers quotes to determine token boundaries.
*/
static inline int	count_tokens(char *input_str)
{
	int		count;
	int		i;
	int		quotes;
	char	current;

	i = 0;
	count = 0;
	quotes = 0;
	while (input_str[i] != '\0')
	{
		while (input_str[i] != '\0' && is_whitespace(input_str[i]))
			i++;
		if (input_str[i])
			count++;
		while (input_str[i] && (!is_whitespace(input_str[i]) || quotes))
		{
			if (input_str[i] == '"' || input_str[i] == '\'')
			{
				if (quotes && input_str[i] == current)
					quotes = 0;
				else if (!quotes)
				{
					quotes = 1;
					current = input_str[i];
				}
			}
			i++;
		}	
	}
	return (count);
}

/*
* Removes quotes from tokens.
* Handles both single and double quotes, preserving content between them.
*/
static inline void	delete_quotes(t_data *data)
{
	int		token_index;
	int		char_index;
	size_t	len;
	char	quote;

	token_index = 0;
	while (data->token[token_index])
	{
		char_index = 0;
		len = ft_strlen(data->token[token_index]);
		while (data->token[token_index][char_index])
		{
			if (data->token[token_index][char_index] == '\'' || data->token[token_index][char_index] == '"')
			{
				quote = data->token[token_index][char_index];
				ft_memmove(data->token[token_index] + char_index, data->token[token_index] + char_index + 1, len - char_index);
				len--;
				while (data->token[token_index][char_index] && data->token[token_index][char_index] != quote)
					char_index++;
				if (data->token[token_index][char_index] == quote)
				{
					ft_memmove(data->token[token_index] + char_index, data->token[token_index]
						+ char_index + 1, len - char_index);
					len--;
				}
			}
			else
				char_index++;
		}
		token_index++;
	}
}

/*
* Checks and handles quotes in the input string during tokenization.
* Keeps track of opening and closing quotes.
*/
static inline int	handle_quote(char *input_str, char *current_quote, int i)
{
	int	quotes;

	quotes = 0;
	while (input_str[i] && (!is_whitespace(input_str[i]) || quotes))
	{
		if (input_str[i] == '"' || input_str[i] == '\'')
		{
			if (quotes && input_str[i] == *current_quote)
				quotes = 0;
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

/*
* Checks if a character is considered "empty" (whitespace).
* Used to determine token boundaries.
*/
static inline int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
