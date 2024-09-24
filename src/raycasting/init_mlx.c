/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:11:35 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/23 15:06:59 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

void	ver_line(t_cub *cub, t_raycst *raycst)
{
	int	i;

	i = raycst->draw_start;
	if (raycst->draw_start < 0)
		raycst->draw_start = 0;
	if (raycst->draw_end >= height)
		raycst->draw_end = height - 1;
	while (i <= raycst->draw_end)
	{
		cub->img_data[i * width + raycst->x] = raycst->color;
		i++;
	}
}

static int	main_loop(t_cub *cub)
{
	t_raycst	raycst;

	raycst.x = -1;
	setup_raycasting(cub, &raycst);
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_window, cub->mlx_img, 0, 0);
	return (0);
}

static void	calcul_ks_ka(t_cub *cub, double old_dirx,
	double old_planex, bool boolean)
{
	if (boolean == true)
	{
		cub->dirX = cub->dirX * cos(-cub->r_s) - cub->dirY * sin(-cub->r_s);
		cub->dirY = old_dirx * sin(-cub->r_s) + cub->dirY * cos(-cub->r_s);
		cub->planeX = cub->planeX * cos(-cub->r_s)
			- cub->planeY * sin(-cub->r_s);
		cub->planeY = old_planex * sin(-cub->r_s)
			+ cub->planeY * cos(-cub->r_s);
	}
	else
	{
		cub->dirX = cub->dirX * cos(cub->r_s) - cub->dirY * sin(cub->r_s);
		cub->dirY = old_dirx * sin(cub->r_s) + cub->dirY * cos(cub->r_s);
		cub->planeX = cub->planeX * cos(cub->r_s)
			- cub->planeY * sin(cub->r_s);
		cub->planeY = old_planex * sin(cub->r_s) + cub->planeY * cos(cub->r_s);
	}
}

static int	key_press(int key, t_cub *cub, double old_dirx, double old_planex)
{
	old_dirx = cub->dirX;
	old_planex = cub->planeX;
	if (key == K_W)
	{
		if (!cub->m[(int)(cub->posX + cub->dirX * cub->m_s)][(int)(cub->posY)])
			cub->posX += cub->dirX * cub->m_s;
		if (!cub->m[(int)(cub->posX)][(int)(cub->posY + cub->dirY * cub->m_s)])
			cub->posY += cub->dirY * cub->m_s;
	}
	if (key == K_S)
	{
		if (!cub->m[(int)(cub->posX - cub->dirX * cub->m_s)][(int)(cub->posY)])
			cub->posX -= cub->dirX * cub->m_s;
		if (!cub->m[(int)(cub->posX)][(int)(cub->posY - cub->dirY * cub->m_s)])
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

void	init_game(t_cub *cub)
{
	init_data(cub);
	cub->mlx_ptr = mlx_init();
	if (cub->mlx_ptr == NULL)
		malloc_error();
	if (!get_textures(cub))
		return ;
	cub->mlx_window = mlx_new_window(cub->mlx_ptr, width, height, "cub3d");
	cub->mlx_img = mlx_new_image(cub->mlx_ptr, width, height);
	cub->img_data = (int *)mlx_get_data_addr(cub->mlx_img,
			&cub->img.bpp, &cub->img.line_leng, &cub->img.endian);
	if (cub->mlx_window == NULL)
	{
		mlx_destroy_window(cub->mlx_ptr, cub->mlx_window);
		free(cub->mlx_ptr);
		exit (1);
	}
	mlx_loop_hook(cub->mlx_ptr, &main_loop, cub);
	mlx_hook(cub->mlx_window, X_EVENT_KEY_PRESS, 0, &key_press, cub);
	mlx_loop(cub->mlx_ptr);
}
