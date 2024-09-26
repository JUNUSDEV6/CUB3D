/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:13:02 by rdendonc          #+#    #+#             */
/*   Updated: 2024/09/25 11:27:12 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*p;

	p = b;
	i = 0;
	while (i < len)
	{
		p[i] = c;
		i++;
	}
	return (b);
}

/*int	main()
{
	int	a;
	size_t	s;

	a = '.';
	s = 5;

	char str[30] = "Hello je m'appelle Rachel";
	char str2[30] = "Hello je m'appelle Rachel";



	printf("Avant : %s\n", str);
	printf("Apres : %s\n", ft_memset(str, a, s));
	printf("Apres : %s\n", memset(str2, '.', 5*sizeof(char)));
	return (0);
}*/
