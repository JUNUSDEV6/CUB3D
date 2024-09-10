/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:11:35 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/10 14:29:35 by yohanafi         ###   ########.fr       */
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
	
	//int	y;
//
	//y = y1;
	//while (y <= y2)
	//{
	//	mlx_pixel_put(cub->mlx_ptr, cub->mlx_window, x, y, color);
	//	y++;
	//}
}

void	calc(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < width)
	{
		double cameraX = 2 * x / (double)width - 1;
		double rayDirX = cub->dirX + cub->planeX * cameraX;
		double rayDirY = cub->dirY + cub->planeY * cameraX;
		
		int mapX = (int)cub->posX;
		int mapY = (int)cub->posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (cub->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (cub->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub->posY) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - cub->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - cub->posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(height / perpWallDist);

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
		if (worldMap[mapY][mapX] == 1)
			color = 0xFF0000;
		else if (worldMap[mapY][mapX] == 2)
			color = 0x00FF00;
		else if (worldMap[mapY][mapX] == 3)
			color = 0x0000FF;
		else if (worldMap[mapY][mapX] == 4)
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;
		
		if (side == 1)
			color = color / 0.2;

		ver_line(cub, x, drawStart, drawEnd, color);
		
		x++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_window, cub->mlx_img, 0, 0);
}

int	main_loop(t_cub *cub)
{
	calc(cub);
	// mlx_put_image_to_window(cub->mlx, info->win, &info->img, 0, 0);

	return (0);
}

int	key_press(int key, t_cub *cub)
{
	if (key == K_W)
	{
		if (!worldMap[(int)(cub->posX + cub->dirX * cub->m_s)][(int)(cub->posY)])
			cub->posX += cub->dirX * cub->m_s;
		if (!worldMap[(int)(cub->posX)][(int)(cub->posY + cub->dirY * cub->m_s)])
			cub->posY += cub->dirY * cub->m_s;
	}
	//move backwards if no wall behind you
	if (key == K_S)
	{
		if (!worldMap[(int)(cub->posX - cub->dirX * cub->m_s)][(int)(cub->posY)])
			cub->posX -= cub->dirX * cub->m_s;
		if (!worldMap[(int)(cub->posX)][(int)(cub->posY - cub->dirY * cub->m_s)])
			cub->posY -= cub->dirY * cub->m_s;
	}
	//rotate to the right
	if (key == K_D)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = cub->dirX;
		cub->dirX = cub->dirX * cos(-cub->r_s) - cub->dirY * sin(-cub->r_s);
		cub->dirY = oldDirX * sin(-cub->r_s) + cub->dirY * cos(-cub->r_s);
		double oldPlaneX = cub->planeX;
		cub->planeX = cub->planeX * cos(-cub->r_s) - cub->planeY * sin(-cub->r_s);
		cub->planeY = oldPlaneX * sin(-cub->r_s) + cub->planeY * cos(-cub->r_s);
	}
	//rotate to the left
	if (key == K_A)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = cub->dirX;
		cub->dirX = cub->dirX * cos(cub->r_s) - cub->dirY * sin(cub->r_s);
		cub->dirY = oldDirX * sin(cub->r_s) + cub->dirY * cos(cub->r_s);
		double oldPlaneX = cub->planeX;
		cub->planeX = cub->planeX * cos(cub->r_s) - cub->planeY * sin(cub->r_s);
		cub->planeY = oldPlaneX * sin(cub->r_s) + cub->planeY * cos(cub->r_s);
	}
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
	//cub->img.img_ptr = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	//if (cub->img.img_ptr == NULL)
	//{
	//	free(cub->mlx_ptr);
	//	malloc_error();
	//}
	//cub->img.pixels_ptr = 
}



