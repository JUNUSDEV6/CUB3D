/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:27:56 by rdendonc          #+#    #+#             */
/*   Updated: 2024/09/25 11:27:57 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*clean_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	if (stash[i] == '\n')
		i++;
	j = i;
	while (stash[j])
		j++;
	new_stash = ft_calloc((j + 1), sizeof(char));
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[i] != '\0')
		new_stash[j++] = stash[i++];
	free(stash);
	return (new_stash);
}

char	*create_line(char *stash)
{
	char	*line;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!stash[0])
		return (NULL);
	while (stash[len] != '\0' && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*create_stash(int fd, char *stash)
{
	char	*buf;
	int		text_read;

	if (!stash)
		return (NULL);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (ft_free_gnl(stash, NULL));
	text_read = 1;
	while (text_read > 0)
	{
		text_read = read(fd, buf, BUFFER_SIZE);
		if (text_read == -1)
			return (ft_free_gnl(stash, buf));
		buf[text_read] = '\0';
		stash = ft_strjoin(stash, buf);
		if (!stash)
			return (NULL);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (stash == NULL)
		stash = ft_calloc(1, sizeof(char));
	if (!stash)
		return (NULL);
	stash = create_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = create_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = clean_stash(stash);
	return (line);
}
