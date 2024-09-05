#include "library.h"

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
