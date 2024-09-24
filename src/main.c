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
	cub->start_i = 0;
	cub->start_j = 0;
	cub->start_dir = 0;
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	init_cub(&cub);
	if (main_parsing(&cub, argc, argv))
		ft_exit(&cub, NULL, EXIT_FAILURE);
	//print_tab(cub.map);
	//cub.mlx_ptr = mlx_init(); ?????????????
	init_game(&cub);
	//execution(&cub);
	free_all(&cub);
	//system("leaks cub3d");
	return (0);
}
