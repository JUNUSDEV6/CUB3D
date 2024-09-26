/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:27:33 by rdendonc          #+#    #+#             */
/*   Updated: 2024/09/25 11:27:34 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	if (n == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str == 0)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**ft_freeall(char **tab)
{
	size_t	j;

	j = 0;
	while (tab[j])
	{
		free(tab[j]);
		j++;
	}
	free(tab);
	return (NULL);
}

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	tabsize;
	size_t	i;

	i = 0;
	tabsize = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != c)
			|| (s[i] == c && s[i + 1] != '\0' && s[i + 1] != c))
			tabsize++;
		i++;
	}
	return (tabsize);
}

char	**ft_split(char const *s, char c)
{
	char	**new_str;
	size_t	i;
	size_t	k;
	size_t	start;

	i = 0;
	k = 0;
	if (!s)
		return (0);
	new_str = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!new_str)
		return (NULL);
	while (i < ft_wordcount(s, c) && s[k] != '\0')
	{
		while (s[k] == c)
			k++;
		start = k;
		while (s[k] != c && s[k] != '\0')
			k++;
		new_str[i] = ft_strndup(&s[start], k - start);
		if (new_str[i++] == 0)
			return (ft_freeall(new_str));
	}
	new_str[i] = NULL;
	return (new_str);
}
