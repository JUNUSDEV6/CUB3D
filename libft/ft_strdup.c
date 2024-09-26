/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:27:35 by rdendonc          #+#    #+#             */
/*   Updated: 2024/09/25 11:27:36 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*p;
	int		i;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	p = str;
	while (*s1 != '\0')
		*p++ = *s1++;
	*p = '\0';
	return (str);
}
