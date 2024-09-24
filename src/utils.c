#include "library.h"

void	ft_exit(t_cub *cub, char *msg, int code)
{
	free_all(cub);
	if (msg)
		error(msg);
	//system("leaks cub3d");
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

void	free_all(t_cub *cub)
{
	if (cub->cub)
		free_tab(cub->cub);
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
	close(cub->fd_cub);
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
