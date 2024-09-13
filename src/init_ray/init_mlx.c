/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:11:35 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/13 14:46:00 by yohanafi         ###   ########.fr       */
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

int	main_loop(t_cub *cub)
{
	t_raycst	raycst;

	setup_raycasting(cub, &raycst);
	//calc(cub);
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



