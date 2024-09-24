#include "library.h"

static void	*create_img(t_cub *cub, char *direction)
{
	char	*path;
	void	*img;
	char	**tab;

	path = find_path(cub->cub, direction, NULL, NULL);
	if (!path)
	{
		ft_putstr_fd("Error: Texture path not found\n", 2);
		return (NULL);
	}
	img = mlx_xpm_file_to_image(cub->mlx_ptr, path, &cub->img_w, &cub->img_h);
	if (!img)
	{
		ft_putstr_fd("Error: Texture loading failed\n", 2);
		return (NULL);
	}
	free(path);
	return (img);
}

int	get_textures(t_cub *cub)
{
	cub->textures[0] = create_img(cub, "NO");
	if (!cub->textures[0])
		return (error("Error: Missing NO texture"));

	// Charger la texture Sud (SO)
	cub->textures[1] = create_img(cub, "SO");
	if (!cub->textures[1])
		return (error("Error: Missing SO texture"));

	// Charger la texture Ouest (WE)
	cub->textures[2] = create_img(cub, "WE");
	if (!cub->textures[2])
		return (error("Error: Missing WE texture"));

	// Charger la texture Est (EA)
	cub->textures[3] = create_img(cub, "EA");
	if (!cub->textures[3])
		return (error("Error: Missing EA texture"));

	return (1);
}
