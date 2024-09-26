/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdendonc <rdendonc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:07:04 by yohanafi          #+#    #+#             */
/*   Updated: 2024/09/25 12:20:55 by rdendonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

void	ft_exit(t_cub *cub, char *msg, int code)
{
	free_all(cub);
	close(cub->fd_cub);
	if (msg)
		error(msg);
	exit(code);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

static void	free_tab_int(int **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void	free_all(t_cub *cub)
{
	if (cub->cub)
		free_tab(cub->cub);
	if (cub->m)
		free_tab_int(cub->m);
	if (cub->map)
		free_tab(cub->map);
	if (cub->no_txr)
		free(cub->no_txr);
	if (cub->so_txr)
		free(cub->so_txr);
	if (cub->we_txr)
		free(cub->we_txr);
	if (cub->ea_txr)
		free(cub->ea_txr);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
	{
		printf("(null)\n");
		return ;
	}
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}
