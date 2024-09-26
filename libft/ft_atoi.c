/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:26:43 by rdendonc          #+#    #+#             */
/*   Updated: 2024/09/25 11:26:44 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long long	num;
	int					i;
	int					neg;

	num = 0;
	i = 0;
	neg = 1;
	while (str[i] == 32 || ((str[i] >= 9) && (str[i] <= 13)))
		i++;
	if ((str[i] == 45) || (str[i] == 43))
	{
		if (str[i] == 45)
			neg = -1;
		i++;
	}
	while ((str[i] != '\0') && (str[i] >= '0') && (str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		if (num > 9223372036854775807 && neg == 1)
			return (-1);
		if (num > 9223372036854775807 && neg == -1)
			return (0);
		i++;
	}
	return (neg * num);
}
