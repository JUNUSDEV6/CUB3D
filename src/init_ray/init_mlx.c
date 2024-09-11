/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:11:35 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/11 14:49:33 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

void	malloc_error(void)
{
	perror("error malloc");
	exit(1);
}

#define CEILING_COLOR 0x000000  // Light Blue color for the ceiling
#define FLOOR_COLOR   0x9000FF  // Brown color for the floor

int	worldMap[24][24] = {
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
						};

void	ver_line(t_cub *cub, int x, int y1, int y2, int color)
{
	if (y1 < 0)
		y1 = 0;
	if (y2 >= height)
		y2 = height - 1;
	
	for (int i = y1; i <= y2; i++)
	{
		cub->img_data[i * width + x] = color;
	}
}

void	calc(t_cub *cub)
{
	t_raycst	raycst;
	
	int	x;

	x = 0;
	while (x < width)
	{
		raycst.camera_x = 2 * x / (double)width - 1;
		raycst.ray_dir_x = cub->dirX + cub->planeX * raycst.camera_x;
		raycst.ray_dir_y = cub->dirY + cub->planeY * raycst.camera_x;
		raycst.map_x = (int)cub->posX;
		raycst.map_y = (int)cub->posY;
		 //length of ray from one x or y-side to next x or y-side
		raycst.delta_dist_x = (raycst.ray_dir_x == 0) ? 1e30 : fabs(1 / raycst.ray_dir_x);
		raycst.delta_dist_y = (raycst.ray_dir_y == 0) ? 1e30 : fabs(1 / raycst.ray_dir_y);
		//what direction to step in x or y-direction (either +1 or -1)
		
		raycst.hit = 0; //was there a wall raycst.hit?
		//raycst.side; //was a NS or a EW wall raycst.hit?

		if (raycst.ray_dir_x < 0)
		{
			raycst.step_x = -1;
			raycst.side_dist_x = (cub->posX - raycst.map_x) * raycst.delta_dist_x;
		}
		else
		{
			raycst.step_x = 1;
			raycst.side_dist_x = (raycst.map_x + 1.0 - cub->posX) * raycst.delta_dist_x;
		}
		if (raycst.ray_dir_y < 0)
		{
			raycst.step_y = -1;
			raycst.side_dist_y = (cub->posY - raycst.map_y) * raycst.delta_dist_y;
		}
		else
		{
			raycst.step_y = 1;
			raycst.side_dist_y = (raycst.map_y + 1.0 - cub->posY) * raycst.delta_dist_y;
		}

		while (raycst.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (raycst.side_dist_x < raycst.side_dist_y)
			{
				raycst.side_dist_x += raycst.delta_dist_x;
				raycst.map_x += raycst.step_x;
				raycst.side = 0;
			}
			else
			{
				raycst.side_dist_y += raycst.delta_dist_y;
				raycst.map_y += raycst.step_y;
				raycst.side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[raycst.map_x][raycst.map_y] > 0) raycst.hit = 1;
		}
		if (raycst.side == 0)
			raycst.per_wall_dist = (raycst.map_x - cub->posX + (1 - raycst.step_x) / 2) / raycst.ray_dir_x;
		else
			raycst.per_wall_dist = (raycst.map_y - cub->posY + (1 - raycst.step_y) / 2) / raycst.ray_dir_y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(height / raycst.per_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		if(drawEnd >= height)
			drawEnd = height - 1;

		for (int y = 0; y < drawStart; y++)
			if (y >= 0 && y < height)
				cub->img_data[y * width + x] =  CEILING_COLOR;
		
		for (int y = drawEnd + 1; y < height; y++)
			if (y >= 0 && y < height)
				cub->img_data[y * width + x] = FLOOR_COLOR;

		int	color;
		if (worldMap[raycst.map_y][raycst.map_x] == 1)
			color = 0xFF0000;
		else if (worldMap[raycst.map_y][raycst.map_x] == 2)
			color = 0x00FF00;
		else if (worldMap[raycst.map_y][raycst.map_x] == 3)
			color = 0x0000FF;
		else if (worldMap[raycst.map_y][raycst.map_x] == 4)
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;
		
		if (raycst.side == 1)
			color = color / 0.2;

		ver_line(cub, x, drawStart, drawEnd, color);
		
		x++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_window, cub->mlx_img, 0, 0);
}

int	main_loop(t_cub *cub)
{
	calc(cub);
	return (0);
}

static void	calcul_ks_ka(t_cub *cub, double old_dirx, double old_planex, bool boolean)
{
	if (boolean == true)
	{
		cub->dirX = cub->dirX * cos(-cub->r_s) - cub->dirY * sin(-cub->r_s);
		cub->dirY = old_dirx * sin(-cub->r_s) + cub->dirY * cos(-cub->r_s);
		cub->planeX = cub->planeX * cos(-cub->r_s) - cub->planeY * sin(-cub->r_s);
		cub->planeY = old_planex * sin(-cub->r_s) + cub->planeY * cos(-cub->r_s);
	}
	else
	{
		cub->dirX = cub->dirX * cos(cub->r_s) - cub->dirY * sin(cub->r_s);
		cub->dirY = old_dirx * sin(cub->r_s) + cub->dirY * cos(cub->r_s);
		cub->planeX = cub->planeX * cos(cub->r_s) - cub->planeY * sin(cub->r_s);
		cub->planeY = old_planex * sin(cub->r_s) + cub->planeY * cos(cub->r_s);
	}
}

int	key_press(int key, t_cub *cub, double old_dirx, double old_planex)
{
	old_dirx = cub->dirX;
	old_planex = cub->planeX;
	if (key == K_W)
	{
		if (!worldMap[(int)(cub->posX + cub->dirX * cub->m_s)][(int)(cub->posY)])
			cub->posX += cub->dirX * cub->m_s;
		if (!worldMap[(int)(cub->posX)][(int)(cub->posY + cub->dirY * cub->m_s)])
			cub->posY += cub->dirY * cub->m_s;
	}
	if (key == K_S)
	{
		if (!worldMap[(int)(cub->posX - cub->dirX * cub->m_s)][(int)(cub->posY)])
			cub->posX -= cub->dirX * cub->m_s;
		if (!worldMap[(int)(cub->posX)][(int)(cub->posY - cub->dirY * cub->m_s)])
			cub->posY -= cub->dirY * cub->m_s;
	}
	if (key == K_D)
		calcul_ks_ka(cub, old_dirx, old_planex, true);
	if (key == K_A)
		calcul_ks_ka(cub, old_dirx, old_planex, false);
	if (key == K_ESC)
		exit(0);
	return (0);
}


void	init_cub(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();

	cub->posX = 12;
	cub->posY = 5;
	cub->dirX = -1;
	cub->dirY = 0;
	cub->planeX = 0;
	cub->planeY = 0.66;
	cub->m_s = 0.05;
	cub->r_s = 0.05;

	if (cub->mlx_ptr == NULL)
		malloc_error();
	cub->mlx_window = mlx_new_window(cub->mlx_ptr, width, height, "cub3d");
	cub->mlx_img = mlx_new_image(cub->mlx_ptr, width, height);
	cub->img_data = (int *)mlx_get_data_addr(cub->mlx_img, &cub->img.bpp, &cub->img.line_leng, &cub->img.endian);
	if (cub->mlx_window == NULL)
	{
		mlx_destroy_window(cub->mlx_ptr, cub->mlx_window);
		free(cub->mlx_ptr);
		malloc_error();
	}
	mlx_loop_hook(cub->mlx_ptr, &main_loop, cub);
	mlx_hook(cub->mlx_window, X_EVENT_KEY_PRESS, 0, &key_press, cub);
	mlx_loop(cub->mlx_ptr);
}



