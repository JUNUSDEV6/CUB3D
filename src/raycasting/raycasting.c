/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:01:42 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/25 12:18:21 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

static void	calcul_ray_delta_dist(t_cub *cub, t_raycst *raycst)
{
	raycst->camera_x = 2 * raycst->x / (double)WIDTH - 1;
	raycst->ray_dir_x = cub->dirx + cub->planex * raycst->camera_x;
	raycst->ray_dir_y = cub->diry + cub->planey * raycst->camera_x;
	raycst->map_x = (int)cub->posx;
	raycst->map_y = (int)cub->posy;
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
		raycst->side_dist_x = (cub->posx - raycst->map_x)
			* raycst->delta_dist_x;
	}
	else
	{
		raycst->step_x = 1;
		raycst->side_dist_x = (raycst->map_x + 1.0 - cub->posx)
			* raycst->delta_dist_x;
	}
	if (raycst->ray_dir_y < 0)
	{
		raycst->step_y = -1;
		raycst->side_dist_y = (cub->posy - raycst->map_y)
			* raycst->delta_dist_y;
	}
	else
	{
		raycst->step_y = 1;
		raycst->side_dist_y = (raycst->map_y + 1.0 - cub->posy)
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
	if (cub->m[raycst->map_x][raycst->map_y] > 0)
		raycst->hit = 1;
}

static void	draw_coloring(t_cub *cub, t_raycst *raycst)
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
	raycst->tex_x = (int)(raycst->wall_x * (double)TEXWIDTH);
	if (raycst->side == 0 && raycst->ray_dir_x > 0)
		raycst->tex_x = TEXWIDTH - raycst->tex_x - 1;
	if (raycst->side == 1 && raycst->ray_dir_y < 0)
		raycst->tex_x = TEXWIDTH - raycst->tex_x - 1;
	raycst->step = 1.0 * TEXHEIGHT / raycst->line_height;
	raycst->tex_pos = (raycst->draw_start - HEIGHT / 2 + raycst->line_height
			/ 2) * raycst->step;
	while (++i < raycst->draw_start)
		if (i >= 0 && i < HEIGHT)
			cub->img_data[i * WIDTH + raycst->x] = cub->c_color;
	draw_textures(cub, raycst, -1, 0);
}

void	setup_raycasting(t_cub *cub, t_raycst *raycst)
{
	while (++(raycst->x) < WIDTH)
	{
		calcul_ray_delta_dist(cub, raycst);
		calculate_step_and_side_dist(cub, raycst);
		while (raycst->hit == 0)
			launch_beam(cub, raycst);
		if (raycst->side == 0 && raycst->ray_dir_x != 0)
			raycst->wall_dist = (raycst->map_x - cub->posx
					+ (1 - raycst->step_x) / 2) / raycst->ray_dir_x;
		else
			raycst->wall_dist = (raycst->map_y - cub->posy
					+ (1 - raycst->step_y) / 2) / raycst->ray_dir_y;
		raycst->line_height = (int)(HEIGHT / raycst->wall_dist);
		raycst->draw_start = -raycst->line_height / 2 + HEIGHT / 2;
		if (raycst->draw_start < 0)
			raycst->draw_start = 0;
		raycst->draw_end = raycst->line_height / 2 + HEIGHT / 2;
		if (raycst->draw_end >= HEIGHT)
			raycst->draw_end = HEIGHT - 1;
		if (raycst->side == 0)
			raycst->wall_x = cub->posy + raycst->wall_dist * raycst->ray_dir_y;
		else
			raycst->wall_x = cub->posx + raycst->wall_dist * raycst->ray_dir_x;
		draw_coloring(cub, raycst);
	}
}
