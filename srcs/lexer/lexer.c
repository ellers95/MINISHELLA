/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:32:34 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/15 00:05:50 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool				lexer(char *str, t_data *data);
static inline int	count_tokens(char *str);
static inline void	del_quotes(t_data *data);
static inline int	quote_chk(char *str, char *cur_quo, int i);
static inline int	empties(char c);

/*
* Main lexical analysis function.
* Tokenizes the input string and handles quotes and environment variables.
*/
bool	lexer(char *str, t_data *data)
{
	int		i;
	int		token_index;
	char	cur_quo;
	int		start;

	i = 0;
	token_index = 0;
	cur_quo = 0;
	data->tok_num = count_tokens(str);
	data->token = ft_calloc((data->tok_num + 1), sizeof(char *));
	if (!data->token)
		return (false);
	while(token_index < data->tok_num && str[i])
	{
		while (str[i] && empties(str[i]))
			i++;
		if(str[i])
		{
			start = i;
			i = quote_chk(str, &cur_quo, i);	
			data->token[token_index] = ft_calloc(i - start + 1, sizeof(char));
			if (!data->token[token_index])
				return (false);
			ft_strlcpy(data->token[token_index], &str[start], i - start + 1);
			data->token[token_index] = env_variable_check(data->token[token_index], data->env, data);
			token_index++;
		}
	}
	del_quotes(data);
	return (true);
}

/*
* Counts the number of tokens in the input string.
* Considers quotes to determine token boundaries.
*/
static inline int	count_tokens(char *str)
{
	int		count;
	int		i;
	int		quotes;
	char	current;

	i = 0;
	count = 0;
	quotes = 0;
	while (str[i] !=  '\0')
	{
		while (str[i] != '\0' && empties(str[i]))
			i++;
		if (str[i])
			count++;
		while(str[i] && (!empties(str[i]) || quotes))
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				if (quotes && str[i] == current)
					quotes = 0;
				else if (!quotes)
				{
					quotes= 1;
					current = str[i];
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
static inline void	del_quotes(t_data *data)
{
	int		i;
	int		j;
	size_t	len;
	char	quote;

	i = 0;
	while (data->token[i])
	{
		j = 0;
		len = ft_strlen(data->token[i]);
		while (data->token[i][j])
		{
			// Check for both single and double quotes
			if (data->token[i][j] == '\'' || data->token[i][j] == '"')
			{
				quote = data->token[i][j];
				// Remove the opening quote
				ft_memmove(data->token[i] + j, data->token[i] + j + 1, len - j);
				len--;
				// Find the matching closing quote
				while (data->token[i][j] && data->token[i][j] != quote)
					j++;
				if (data->token[i][j] == quote)
				{
					// Remove the closing quote
					ft_memmove(data->token[i] + j, data->token[i] + j + 1, len - j);
					len--;
				}
			}
			else
			{
				j++;
			}
		}
		i++;
	}
}

/*
* Checks and handles quotes in the input string during tokenization.
* Keeps track of opening and closing quotes.
*/
static inline int	quote_chk(char *str, char *cur_quo, int i)
{
	int quotes;

	quotes = 0;
	while (str[i] && (!empties(str[i]) || quotes))
	{
		if(str[i] == '"' || str[i] == '\'')
		{
			if (quotes && str[i] == *cur_quo)
				quotes = 0;
			else if (!quotes)
			{
				quotes = 1;
				*cur_quo = str[i];
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
static inline int	empties(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
