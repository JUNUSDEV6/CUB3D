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

int	main(int argc, char **argv)
{
	t_cub	cub;
	(void)argv;
	(void)argc;

	//cub.mlx_ptr = mlx_init();
	//if (main_parsing(&cub, argc, argv))
	//{
	//	//system("leaks cub3d");
	//	return (1);
	//}
	init_cub(&cub);
	mlx_loop(cub.mlx_ptr);
	free_all(&cub);
	//system("leaks cub3d");
	return (0);
}
