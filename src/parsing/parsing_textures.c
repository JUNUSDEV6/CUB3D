/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:51:41 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/24 15:51:43 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

char	*find_path(char **cub, char *dir, char *path, char **tab)
{
	int		i;

	if (!cub || !dir)
		return (NULL);
	i = 0;
	while (cub[i])
	{
		if (tab)
			free_tab(tab);
		tab = ft_split(cub[i], ' ');
		if (ft_strnstr(tab[0], dir, ft_strlen(dir)))
		{
			if (!tab[1])
				return (NULL);
			path = ft_strdup(tab[1]);
			break ;
		}
		if (cub[i])
			i++;
	}
	free_tab(tab);
	return (path);
}

static void	*create_img(t_cub *cub, char *direction)
{
	char	*path;
	void	*img;
	char	**tab;

	path = NULL;
	img = NULL;
	tab = NULL;
	path = find_path(cub->cub, direction, path, tab);
	if (!path)
		return (NULL);
	if (open(path, O_RDONLY) <= 0)
	{
		free(path);
		return (NULL);
	}
	return (path);
}

int	parsing_textures(t_cub *cub)
{
	cub->no_txr = create_img(cub, "NO");
	if (!cub->no_txr)
		return (error("Missing or wrong link for textures NO"));
	cub->so_txr = create_img(cub, "SO");
	if (!cub->so_txr)
		return (error("Missing or wrong link for textures SO"));
	cub->we_txr = create_img(cub, "WE");
	if (!cub->we_txr)
		return (error("Missing or wrong link for textures WE"));
	cub->ea_txr = create_img(cub, "EA");
	if (!cub->ea_txr)
		return (error("Missing or wrong link for textures EA"));
	return (0);
}
