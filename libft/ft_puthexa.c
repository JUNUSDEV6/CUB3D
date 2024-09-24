/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:45:18 by rdendonc          #+#    #+#             */
/*   Updated: 2024/09/17 12:12:51 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(unsigned int nbr, const char *base, int *i, char *result)
{
	unsigned int	base_len;

	base_len = ft_strlen(base);
	if (nbr >= base_len)
	{
		if (ft_putnbr_base(nbr / base_len, base, i, result) == -1)
			return (-1);
		if (ft_putnbr_base(nbr % base_len, base, i, result) == -1)
			return (-1);
	}
	else
	{
		result[*i] = base[nbr];
		(*i)++;
	}
	return (0);
}

char	*ft_puthexa(unsigned int nbr)
{
	char			*base;
	char			*result;
	int				i;

	base = "0123456789ABCDEF";
	result = ft_calloc(sizeof(char), 9);
	i = 0;
	if (!result)
		return (NULL);
	if (ft_putnbr_base(nbr, base, &i, result) == -1)
	{
		free(result);
		return (NULL);
	}
	return (result);
}
