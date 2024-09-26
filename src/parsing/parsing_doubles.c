/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_doubles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:51:28 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/24 15:51:30 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

static int	double_infos_check_utils(char **cub, char *element, int i)
{
	char	**tab;

	tab = NULL;
	while (cub[++i] && i < 7)
	{
		if (tab)
			free_tab(tab);
		tab = ft_split(cub[i], ' ');
		if (cub[i] && ft_strnstr(tab[0], element, ft_strlen(tab[0])))
		{
			free_tab(tab);
			return (1);
		}
	}
	if (tab)
		free_tab(tab);
	return (0);
}

static int	double_infos_check(char **cub, char *element)
{
	int		i;
	char	**tab;

	if (!cub || !element)
		return (1);
	i = 0;
	tab = NULL;
	while (cub[i] && i < 7)
	{
		if (tab)
			free_tab(tab);
		tab = ft_split(cub[i], ' ');
		if (ft_strnstr(tab[0], element, ft_strlen(element)))
		{
			if (double_infos_check_utils(cub, element, i))
			{
				free_tab(tab);
				return (1);
			}
		}
		if (cub[i])
			i++;
	}
	free_tab(tab);
	return (0);
}

int	double_infos(char **cub)
{
	if (double_infos_check(cub, "NO"))
		return (error("Double NO texture"));
	if (double_infos_check(cub, "SO"))
		return (error("Double SO texture"));
	if (double_infos_check(cub, "WE"))
		return (error("Double WE texture"));
	if (double_infos_check(cub, "EA"))
		return (error("Double EA texture"));
	if (double_infos_check(cub, "F"))
		return (error("Double F texture"));
	if (double_infos_check(cub, "C"))
		return (error("Double C texture"));
	return (0);
}
