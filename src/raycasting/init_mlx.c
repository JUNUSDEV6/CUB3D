/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:11:35 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/25 12:16:47 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

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
		cub->dirx = cub->dirx * cos(-cub->r_s) - cub->diry * sin(-cub->r_s);
		cub->diry = old_dirx * sin(-cub->r_s) + cub->diry * cos(-cub->r_s);
		cub->planex = cub->planex * cos(-cub->r_s)
			- cub->planey * sin(-cub->r_s);
		cub->planey = old_planex * sin(-cub->r_s)
			+ cub->planey * cos(-cub->r_s);
	}
	else
	{
		cub->dirx = cub->dirx * cos(cub->r_s) - cub->diry * sin(cub->r_s);
		cub->diry = old_dirx * sin(cub->r_s) + cub->diry * cos(cub->r_s);
		cub->planex = cub->planex * cos(cub->r_s)
			- cub->planey * sin(cub->r_s);
		cub->planey = old_planex * sin(cub->r_s) + cub->planey * cos(cub->r_s);
	}
}

static	void	kd_ka(t_cub *cub, bool boolean)
{
	if (boolean == true)
	{
		if (!cub->m[(int)(cub->posx + cub->planex * cub->m_s)]
			[(int)(cub->posy)])
			cub->posx += cub->planex * cub->m_s;
		if (!cub->m[(int)(cub->posx)]
			[(int)(cub->posy + cub->planey * cub->m_s)])
			cub->posy += cub->planey * cub->m_s;
	}
	else
	{
		if (!cub->m[(int)(cub->posx - cub->planex * cub->m_s)]
			[(int)(cub->posy)])
			cub->posx -= cub->planex * cub->m_s;
		if (!cub->m[(int)(cub->posx)]
			[(int)(cub->posy - cub->planey * cub->m_s)])
			cub->posy -= cub->planey * cub->m_s;
	}
}

static int	key_press(int key, t_cub *cub)
{
	if (key == K_W)
	{
		if (!cub->m[(int)(cub->posx + cub->dirx * cub->m_s)][(int)(cub->posy)])
			cub->posx += cub->dirx * cub->m_s;
		if (!cub->m[(int)(cub->posx)][(int)(cub->posy + cub->diry * cub->m_s)])
			cub->posy += cub->diry * cub->m_s;
	}
	if (key == K_S)
	{
		if (!cub->m[(int)(cub->posx - cub->dirx * cub->m_s)][(int)(cub->posy)])
			cub->posx -= cub->dirx * cub->m_s;
		if (!cub->m[(int)(cub->posx)][(int)(cub->posy - cub->diry * cub->m_s)])
			cub->posy -= cub->diry * cub->m_s;
	}
	if (key == K_D)
		kd_ka(cub, true);
	if (key == K_A)
		kd_ka(cub, false);
	if (key == K_AR_R)
		calcul_ks_ka(cub, cub->dirx, cub->planex, true);
	if (key == K_AR_L)
		calcul_ks_ka(cub, cub->dirx, cub->planex, false);
	if (key == K_ESC)
		ft_exit(cub, NULL, 0);
	return (0);
}

void	init_game(t_cub *cub)
{
	init_data(cub);
	cub->mlx_ptr = mlx_init();
	if (cub->mlx_ptr == NULL)
		return ;
	if (!get_textures(cub))
		return ;
	cub->mlx_window = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	cub->mlx_img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
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
