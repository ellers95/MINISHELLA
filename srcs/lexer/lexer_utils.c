/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:52:32 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/19 08:26:44 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Checks if a character is considered "empty" (whitespace).
* Used to determine token boundaries.
*/
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/*
 * Parses the content of a token, handling quoted sections and whitespace.
 * 1. Iterates through the input string until it finds
 * unquoted whitespace or the end of the string
 * 2. Manages the state of quoting, tracking whether we're inside or outside quotes
 * 3. Handles both single and double quotes, allowing for nested quoting

*/
static inline int	parse_token_content(char *input_str, int i, int *quotes,
						char *current)
{
	while (input_str[i] && (!is_whitespace(input_str[i]) || *quotes))
	{
		if ((input_str[i] == '"' || input_str[i] == '\'')
			&& (!*quotes || input_str[i] == *current))
		{
			*quotes = !*quotes;
			if (*quotes)
				*current = input_str[i];
			else
				*current = 0;
		}
		i++;
	}
	return (i);
}

/*
* Counts the number of tokens in the input string.
* Considers quotes to determine token boundaries.
*/
int	count_tokens(char *input_str)
{
	int		count;
	int		i;
	int		quotes;
	char	current;

	i = 0;
	count = 0;
	quotes = 0;
	while (input_str[i])
	{
		while (is_whitespace(input_str[i]))
			i++;
		if (input_str[i])
			count++;
		i = parse_token_content(input_str, i, &quotes, &current);
	}
	return (count);
}
