/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:51:17 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/24 15:51:18 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

int	get_hexadecimal(char **colors)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	return (r << 16 | g << 8 | b);
}

void	get_colors(t_cub *cub)
{
	int		i;
	char	**floor;
	char	**ceiling;

	i = 0;
	while (!ft_strnstr(cub->cub[i], "F", 1))
		i++;
	floor = create_colors_tab(cub->cub, i);
	i = 0;
	while (!ft_strnstr(cub->cub[i], "C", 1))
		i++;
	ceiling = create_colors_tab(cub->cub, i);
	cub->f_color = get_hexadecimal(floor);
	cub->c_color = get_hexadecimal(ceiling);
	free_tab(floor);
	free_tab(ceiling);
}
