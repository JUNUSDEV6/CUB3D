/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:28:49 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/24 12:28:17 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

void	malloc_error(void)
{
	perror("error malloc");
	exit(1);
}

static int **copy_char_to_int_map(t_cub *cub, char **char_map, int i, int j)
{
	int **int_map;
	int max_width = 0;

	while (char_map && char_map[cub->height_m] != NULL)
		cub->height_m++;
	int_map = (int **)malloc(sizeof(int *) * cub->height_m);
	if (!int_map)
		return (NULL);
	while (++i < cub->height_m)
	{
		int_map[i] = (int *)malloc(sizeof(int) * (ft_strlen(char_map[i]) + 1));
		if (!int_map[i])
		{
			while (--i >= 0)
				free(int_map[i]);
			free(int_map);
			return (NULL);
		}
		j = -1;
		while (++j < ft_strlen(char_map[i]))
		{
			if (char_map[i][j] == '0' || char_map[i][j] == '1')
				int_map[i][j] = char_map[i][j] - '0';
		}
	}
	return (int_map);
}

void	draw_textures(t_cub *cub, t_raycst *raycst, int i, int y)
{
	char	*pixel_adrr;
	int		index;

	y = raycst->draw_start -1;
	while (++y < raycst->draw_end)
	{
		raycst->tex_y = (int)raycst->tex_pos & (texHeight - 1);
		raycst->tex_pos += raycst->step;
		pixel_adrr = mlx_get_data_addr(cub->textures[raycst->tex_n],
				&cub->img.bpp, &cub->img.line_leng, &cub->img.endian);
		index = (raycst->tex_y * cub->img.line_leng
				+ raycst->tex_x * (cub->img.bpp / 8));
		raycst->color = *(unsigned int *)(pixel_adrr + index);
		if (raycst->side == 1)
			raycst->color = (raycst->color >> 1) & 8355711;
		if (y >= 0 && y < height)
			cub->img_data[y * width + raycst->x] = raycst->color;
	}
	i = raycst->draw_end - 1;
	while (++i < height)
		if (i >= 0 && i < height)
			cub->img_data[i * width + raycst->x] = cub->f_color;
}

static void	find_direction(t_cub *cub, char direction)
{
	cub->dirX = -1;
	cub->dirY = 0;
	cub->planeX = 0;
	cub->planeY = 0.66;
	if (direction == 'S')
	{
		cub->dirX = 1;
		cub->dirY = 0;
		cub->planeX = 0;
		cub->planeY = -0.66;
	}
	else if (direction == 'W')
	{
		cub->dirX = 0;
		cub->dirY = -1;
		cub->planeX = -0.66;
		cub->planeY = 0;
	}
	else if (direction == 'E')
	{
		cub->dirX = 0;
		cub->dirY = 1;
		cub->planeX = 0.66;
		cub->planeY = 0;
	}
}

void	init_data(t_cub *cub)
{
	cub->posX = cub->start_i + 0.5;
	cub->posY = cub->start_j + 0.5;
	find_direction(cub, cub->start_dir);
	cub->m_s = 0.10;
	cub->r_s = 0.10;
	cub->height_m = 0;
	cub->width_m = 0;
	cub->m = copy_char_to_int_map(cub, cub->map, -1, -1);
}
