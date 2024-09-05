#include "library.h"

static char	*find_path(char **cub, char *dir, char *path, char **tab)
{
	int		i;

	if (!cub || !dir)
		return (NULL);
	i = 0;
	while (cub[i])
	{
		if (tab)
			free_tab(tab);
		tab = ft_split(cub[i], ' ');
		if (ft_strnstr(tab[0], dir, ft_strlen(dir)))
		{
			if (!tab[1])
				return (NULL);
			path = ft_strdup(tab[1]);
			break ;
		}
		if (cub[i])
			i++;
	}
	free_tab(tab);
	return (path);
}

static void	*create_img(t_cub *cub, char *direction)
{
	char	*path;
	void	*img;
	char	**tab;
	//int		img_w;
	//int		img_h;

	path = NULL;
	img = NULL;
	tab = NULL;
	path = find_path(cub->cub, direction, path, tab);
	if (!path)
		return (NULL);
	if (open(path, O_RDONLY) <= 0)
		return (NULL);
	//img = mlx_new_image(cub->mlx_ptr, 64, 64);
	//img = mlx_xpm_file_to_image(cub->mlx_ptr, path, &img_w, &img_h);
	free(path);
	return (img);
}

int	get_textures(t_cub *cub)
{
	cub->no_txr = create_img(cub, "NO");
	if (!cub->no_txr)
		return (error("Missing or wrong link for textures NO"));
	cub->so_txr = create_img(cub, "SO");
	if (!cub->so_txr)
		return (error("Missing or wrong link for textures SO"));
	cub->we_txr = create_img(cub, "WE");
	if (!cub->we_txr)
		return (error("Missing or wrong link for textures WE"));
	cub->ea_txr = create_img(cub, "EA");
	if (!cub->ea_txr)
		return (error("Missing or wrong link for textures EA"));
	return (0);
}

