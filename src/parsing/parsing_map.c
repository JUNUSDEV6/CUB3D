/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:51:38 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/24 15:52:09 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

static char	**init_map(char **cub)
{
	int		start;
	int		lenght;
	char	**map;
	int		i;

	start = 6;
	map = NULL;
	i = 0;
	while (cub[start])
		start++;
	lenght = (start - 6);
	map = (char **)malloc(sizeof(char *) * (lenght + 1));
	if (!map)
		return (NULL);
	start = 6;
	while (i < (lenght))
	{
		map[i] = ft_strdup(cub[start]);
		if (!map[i])
			return (NULL);
		i++;
		start++;
	}
	map[i] = NULL;
	return (map);
}

static void	find_initial_position(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (!cub->map[i][j] || cub->map[i][j] == 'N'
				|| cub->map[i][j] == 'S' || cub->map[i][j] == 'E'
				|| cub->map[i][j] == 'W')
			{
				cub->start_i = i;
				cub->start_j = j;
				cub->start_dir = cub->map[i][j];
				cub->map[i][j] = '0';
				return ;
			}
			if (cub->map[i][j])
				j++;
		}
		if (cub->map[i])
			i++;
	}
}

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

static char	**remove_spaces(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_whitespace(map[i][j]))
				map[i][j] = '1';
			j++;
		}
		i++;
	}
	return (map);
}

int	parsing_map(t_cub *cub)
{
	int		length;
	char	**map_cpy;

	length = 0;
	cub->map = init_map(cub->cub);
	if (!cub->map)
		error("Map does not exist");
	find_initial_position(cub);
	while (cub->map[length])
		length++;
	map_cpy = init_map(cub->cub);
	if (check_map(cub, map_cpy, length))
	{
		free_tab(map_cpy);
		return (1);
	}
	free_tab(map_cpy);
	cub->map = remove_spaces(cub->map);
	return (0);
}
