/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:01:42 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/13 15:48:56 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

#define CEILING_COLOR 0x000000  // Light Blue color for the ceiling
#define FLOOR_COLOR   0x9000FF  // Brown color for the floor

static void	calcul_ray_delta_dist(t_cub *cub, t_raycst *raycst)
{
	raycst->camera_x = 2 * raycst->x / (double)width - 1;
	raycst->ray_dir_x = cub->dirX + cub->planeX * raycst->camera_x;
	raycst->ray_dir_y = cub->dirY + cub->planeY * raycst->camera_x;
	raycst->map_x = (int)cub->posX;
	raycst->map_y = (int)cub->posY;
	if (raycst->ray_dir_x == 0)
		raycst->delta_dist_x = 1e30;
	else
		raycst->delta_dist_x = fabs(1 / raycst->ray_dir_x);
	if (raycst->ray_dir_y == 0)
		raycst->delta_dist_y = 1e30;
	else
		raycst->delta_dist_y = fabs(1 / raycst->ray_dir_y);
}

static void	calculate_step_and_side_dist(t_cub *cub, t_raycst *raycst)
{
	raycst->hit = 0;
	if (raycst->ray_dir_x < 0)
	{
		raycst->step_x = -1;
		raycst->side_dist_x = (cub->posX - raycst->map_x)
			* raycst->delta_dist_x;
	}
	else
	{
		raycst->step_x = 1;
		raycst->side_dist_x = (raycst->map_x + 1.0 - cub->posX)
			* raycst->delta_dist_x;
	}
	if (raycst->ray_dir_y < 0)
	{
		raycst->step_y = -1;
		raycst->side_dist_y = (cub->posY - raycst->map_y)
			* raycst->delta_dist_y;
	}
	else
	{
		raycst->step_y = 1;
		raycst->side_dist_y = (raycst->map_y + 1.0 - cub->posY)
			* raycst->delta_dist_y;
	}
}

static void	launch_beam(t_raycst *raycst)
{
	if (raycst->side_dist_x < raycst->side_dist_y)
	{
		raycst->side_dist_x += raycst->delta_dist_x;
		raycst->map_x += raycst->step_x;
		raycst->side = 0;
	}
	else
	{
		raycst->side_dist_y += raycst->delta_dist_y;
		raycst->map_y += raycst->step_y;
		raycst->side = 1;
	}
	if (worldMap[raycst->map_x][raycst->map_y] > 0)
		raycst->hit = 1;
}

static void	draw_coloring(t_cub *cub, t_raycst *raycst, int x, int y)
{
	while (++x < raycst->draw_start)
		if (x >= 0 && x < height)
			cub->img_data[x * width + raycst->x] = CEILING_COLOR;
	while (++y < height)
		if (y >= 0 && y < height)
			cub->img_data[y * width + raycst->x] = FLOOR_COLOR;
	if (worldMap[raycst->map_y][raycst->map_x] == 1)
		raycst->color = 0xFF0000;
	else if (worldMap[raycst->map_y][raycst->map_x] == 2)
		raycst->color = 0x00FF00;
	else if (worldMap[raycst->map_y][raycst->map_x] == 3)
		raycst->color = 0x0000FF;
	else if (worldMap[raycst->map_y][raycst->map_x] == 4)
		raycst->color = 0xFFFFFF;
	else
		raycst->color = 0xFFFF00;
	if (raycst->side == 1)
		raycst->color = raycst->color / 0.2;
}

void	setup_raycasting(t_cub *cub, t_raycst *raycst)
{
	raycst->x = -1;
	while (++(raycst->x) < width)
	{
		calcul_ray_delta_dist(cub, raycst);
		calculate_step_and_side_dist(cub, raycst);
		while (raycst->hit == 0)
			launch_beam(raycst);
		if (raycst->side == 0)
			raycst->per_wall_dist = (raycst->map_x - cub->posX
					+ (1 - raycst->step_x) / 2) / raycst->ray_dir_x;
		else
			raycst->per_wall_dist = (raycst->map_y - cub->posY
					+ (1 - raycst->step_y) / 2) / raycst->ray_dir_y;
		raycst->line_height = (int)(height / raycst->per_wall_dist);
		raycst->draw_start = -raycst->line_height / 2 + height / 2;
		if (raycst->draw_start < 0)
			raycst->draw_start = 0;
		raycst->draw_end = raycst->line_height / 2 + height / 2;
		if (raycst->draw_end >= height)
			raycst->draw_end = height - 1;
		draw_coloring(cub, raycst, -1, raycst->draw_end);
		ver_line(cub, raycst->x, raycst->draw_start,
			raycst->draw_end, raycst->color);
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_window, cub->mlx_img, 0, 0);
}
