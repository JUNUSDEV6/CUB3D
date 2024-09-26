/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:26:45 by rdendonc          #+#    #+#             */
/*   Updated: 2024/09/25 11:26:46 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *str, size_t n)
{
	unsigned char	*string;
	size_t			i;

	i = 0;
	string = (unsigned char *)str;
	while (i < n)
	{
		string[i] = 0;
		i++;
	}
	str = string;
	return (str);
}
