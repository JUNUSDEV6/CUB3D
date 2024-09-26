/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:27:54 by rdendonc          #+#    #+#             */
/*   Updated: 2024/09/25 11:27:55 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_gnl(char *s1, char *s2)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (NULL);
}

char	*ft_strchr(char const *str, int c)
{
	char	my_c;

	my_c = (char)c;
	while (*str)
	{
		if (*str == my_c)
			return ((char *)str);
		str++;
	}
	if (!my_c)
		return ((char *)str);
	return (NULL);
}
