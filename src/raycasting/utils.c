/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:36:15 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/25 12:06:21 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

static int	**copy_char_to_int_map(t_cub *cub, char **char_map, int i, int j)
{
	int	**map;

	while (char_map && char_map[cub->height_m] != NULL)
		cub->height_m++;
	map = (int **)ft_calloc(sizeof(int *), cub->height_m + 1);
	if (!map)
		return (NULL);
	while (++i < cub->height_m)
	{
		map[i] = (int *)ft_calloc(sizeof(int), (ft_strlen(char_map[i]) + 1));
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return (NULL);
		}
		j = -1;
		while (++j < ft_strlen(char_map[i]))
		{
			if (char_map[i][j] == '0' || char_map[i][j] == '1')
				map[i][j] = char_map[i][j] - '0';
		}
	}
	return (map);
}

void	draw_textures(t_cub *cub, t_raycst *raycst, int i, int y)
{
	char	*pixel_adrr;
	int		index;

	y = raycst->draw_start -1;
	while (++y <= raycst->draw_end)
	{
		raycst->tex_y = (int)raycst->tex_pos & (TEXHEIGHT - 1);
		raycst->tex_pos += raycst->step;
		pixel_adrr = mlx_get_data_addr(cub->textures[raycst->tex_n],
				&cub->img.bpp, &cub->img.line_leng, &cub->img.endian);
		index = (raycst->tex_y * cub->img.line_leng
				+ raycst->tex_x * (cub->img.bpp / 8));
		raycst->color = *(unsigned int *)(pixel_adrr + index);
		if (raycst->side == 1)
			raycst->color = (raycst->color >> 1) & 8355711;
		if (y >= 0 && y < HEIGHT)
			cub->img_data[y * WIDTH + raycst->x] = raycst->color;
	}
	i = raycst->draw_end;
	while (++i < HEIGHT)
		if (i >= 0 && i < HEIGHT)
			cub->img_data[i * WIDTH + raycst->x] = cub->f_color;
}

static void	find_direction(t_cub *cub, char direction)
{
	cub->dirx = -1;
	cub->diry = 0;
	cub->planex = 0;
	cub->planey = 0.66;
	if (direction == 'S')
	{
		cub->dirx = 1;
		cub->diry = 0;
		cub->planex = 0;
		cub->planey = -0.66;
	}
	else if (direction == 'W')
	{
		cub->dirx = 0;
		cub->diry = -1;
		cub->planex = -0.66;
		cub->planey = 0;
	}
	else if (direction == 'E')
	{
		cub->dirx = 0;
		cub->diry = 1;
		cub->planex = 0.66;
		cub->planey = 0;
	}
}

void	init_data(t_cub *cub)
{
	cub->posx = cub->start_i + 0.05;
	cub->posy = cub->start_j + 0.05;
	find_direction(cub, cub->start_dir);
	cub->m_s = 0.30;
	cub->r_s = 0.15;
	cub->height_m = 0;
	cub->width_m = 0;
	cub->m = copy_char_to_int_map(cub, cub->map, -1, -1);
}
