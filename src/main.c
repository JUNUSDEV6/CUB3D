/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:55:15 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/25 11:52:02 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

int	error(char *msg)
{
	if (msg)
	{
		write(2, "Error\n", 6);
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	else
		write(2, "Error\n", 6);
	return (1);
}

void	init_cub(t_cub *cub)
{
	cub->cub = NULL;
	cub->no_txr = NULL;
	cub->so_txr = NULL;
	cub->ea_txr = NULL;
	cub->we_txr = NULL;
	cub->f_color = 0;
	cub->c_color = 0;
	cub->map = NULL;
	cub->m = NULL;
	cub->start_i = 0;
	cub->start_j = 0;
	cub->start_dir = 0;
	cub->mlx_window = NULL;
	cub->mlx_ptr = NULL;
	cub->img.img_ptr = NULL;
	cub->img.pixels_ptr = NULL;
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	init_cub(&cub);
	if (main_parsing(&cub, argc, argv))
		ft_exit(&cub, NULL, EXIT_FAILURE);
	init_game(&cub);
	free_all(&cub);
	return (0);
}
