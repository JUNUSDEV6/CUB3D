/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:27:47 by rdendonc          #+#    #+#             */
/*   Updated: 2024/09/25 11:27:48 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	while ((i < len) && (haystack[i]))
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (i + j < len && haystack[i + j] == needle[j])
			{
				if (needle[j + 1] == '\0')
					return ((char *)&haystack[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>
// int	main(void)
// {
// 	const char	str1[] = "here_doc";
// 	const char	str2[] = "here_do";
// 	size_t	n;

// 	n = sizeof(str1);
// 	printf("Avec strnstr = %s\n", strnstr(str1, str2, n));
// 	printf("Avec ft_strnstr = %s\n", ft_strnstr(str1, str2, n));
// 	return (0);
// }
