/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:15:27 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/17 18:58:06 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_and_ft_free(char **complete_buffer, char *read_buffer)
{
	char	*temp;

	temp = ft_strjoin_gnl(*complete_buffer, read_buffer);
	ft_free(*complete_buffer);
	return (temp);
}

char	*remaining_lines(char *complete_buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (complete_buffer[i] && complete_buffer[i] != '\n')
		i++;
	if (!complete_buffer[i])
	{
		ft_free(complete_buffer);
		return (NULL);
	}
	line = ft_calloc_gnl((ft_strlen_gnl(complete_buffer)
				- i + 1), sizeof(char));
	if (!line)
	{
		ft_free(complete_buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (complete_buffer[i])
		line[j++] = complete_buffer[i++];
	ft_free(complete_buffer);
	return (line);
}

char	*first_line(char *complete_buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!complete_buffer[i])
		return (NULL);
	while (complete_buffer[i] && complete_buffer[i] != '\n')
		i++;
	if (complete_buffer[i] == '\n')
		i += 1;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (complete_buffer[i] && complete_buffer[i] != '\n')
	{
		line[i] = complete_buffer[i];
		i++;
	}
	if (complete_buffer[i] && complete_buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char **complete_buffer)
{
	struct s_vars	t;

	t.read_buffer = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (!t.read_buffer)
		return (join_and_ft_free(complete_buffer, NULL));
	t.bytes_read = 1;
	while (!ft_strchr_gnl(t.read_buffer, '\n') && t.bytes_read > 0)
	{
		t.bytes_read = read(fd, t.read_buffer, BUFFER_SIZE);
		if (t.bytes_read == -1)
		{
			ft_free(*complete_buffer);
			ft_free(t.read_buffer);
			return (NULL);
		}
		t.read_buffer[t.bytes_read] = 0;
		*complete_buffer = join_and_ft_free(complete_buffer, t.read_buffer);
		if (!(*complete_buffer))
		{
			ft_free(t.read_buffer);
			return (NULL);
		}
	}
	ft_free(t.read_buffer);
	return (*complete_buffer);
}

char	*get_next_line(int fd)
{
	static char	*complete_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!complete_buffer)
		complete_buffer = ft_calloc_gnl(1, 1);
	complete_buffer = read_file(fd, &complete_buffer);
	if (!complete_buffer)
		return (NULL);
	line = first_line(complete_buffer);
	if (!line)
	{
		ft_free(complete_buffer);
		complete_buffer = NULL;
		return (NULL);
	}
	complete_buffer = remaining_lines(complete_buffer);
	return (line);
}
