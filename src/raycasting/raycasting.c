/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:01:42 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/24 12:31:18 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

#define CEILING_COLOR 0x00FF00  // Light Blue color for the ceiling
#define FLOOR_COLOR   0x000080 // Brown color for the floor

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

static void	launch_beam(t_cub *cub, t_raycst *raycst)
{
	(void)cub;
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
	if (raycst->map_x < 0 || raycst->map_x >= cub->height_m || 
		raycst->map_y < 0 || raycst->map_y >= cub->width_m)
    {
        raycst->hit = 1;  // Considérer comme un mur pour éviter le crash
        return;
    }
	if (cub->m[raycst->map_x][raycst->map_y] > 0)
		raycst->hit = 1;
}

static void	draw_coloring(t_cub *cub, t_raycst *raycst, int x, int y)
{
	int	i;

	i = -1;
	raycst->wall_x -= floor(raycst->wall_x);
	if (raycst->side == 0 && raycst->ray_dir_x > 0)
		raycst->tex_n = 0;
	else if (raycst->side == 0 && raycst->ray_dir_x <= 0)
		raycst->tex_n = 1;
	else if (raycst->side == 1 && raycst->ray_dir_y > 0)
		raycst->tex_n = 2;
	else
		raycst->tex_n = 3;
	raycst->tex_x = (int)(raycst->wall_x * (double)texWidth);
	if (raycst->side == 0 && raycst->ray_dir_x > 0)
		raycst->tex_x = texWidth - raycst->tex_x - 1;
	if (raycst->side == 1 && raycst->ray_dir_y < 0)
		raycst->tex_x = texWidth - raycst->tex_x - 1;
	raycst->step = 1.0 * texHeight / raycst->line_height;
	raycst->tex_pos = (raycst->draw_start - height / 2 + raycst->line_height
			/ 2) * raycst->step;
	while (++i < raycst->draw_start)
		if (i >= 0 && i < height)
			cub->img_data[i * width + raycst->x] = cub->c_color;
	draw_textures(cub, raycst, -1, 0);
}

void	setup_raycasting(t_cub *cub, t_raycst *raycst)
{
	while (++(raycst->x) < width)
	{
		calcul_ray_delta_dist(cub, raycst);
		calculate_step_and_side_dist(cub, raycst);
		while (raycst->hit == 0)
			launch_beam(cub, raycst);
		if (raycst->side == 0 && raycst->ray_dir_x != 0)
			raycst->wall_dist = (raycst->map_x - cub->posX
					+ (1 - raycst->step_x) / 2) / raycst->ray_dir_x;
		else if (raycst->ray_dir_y != 0)
			raycst->wall_dist = (raycst->map_y - cub->posY
					+ (1 - raycst->step_y) / 2) / raycst->ray_dir_y;
		else
			raycst->wall_dist = 0.1;
		raycst->line_height = (int)(height / raycst->wall_dist);
		raycst->draw_start = -raycst->line_height / 2 + height / 2;
		if (raycst->draw_start < 0)
			raycst->draw_start = 0;
		raycst->draw_end = raycst->line_height / 2 + height / 2;
		if (raycst->draw_end >= height)
			raycst->draw_end = height - 1;
		if (raycst->side == 0)
			raycst->wall_x = cub->posY + raycst->wall_dist * raycst->ray_dir_y;
		else
			raycst->wall_x = cub->posX + raycst->wall_dist * raycst->ray_dir_x;
		draw_coloring(cub, raycst, -1, raycst->draw_end);
	}
}
