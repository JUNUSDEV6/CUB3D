/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:26:48 by rdendonc          #+#    #+#             */
/*   Updated: 2024/09/25 11:26:49 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count_n, size_t size_n)
{
	void	*ptr;

	if (!count_n || !size_n)
		return (malloc(0));
	if ((count_n * size_n) / count_n != size_n)
		return (NULL);
	ptr = (void *)malloc(count_n * size_n);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count_n * size_n);
	return (ptr);
}
