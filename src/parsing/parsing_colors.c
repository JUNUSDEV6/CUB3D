#include "library.h"

int	parsing_colors(char **cub)
{
	int		i;
	int		j;
	char	**colors;

	i = 0;
	j = 0;
	colors = NULL;
	while (cub[i])
	{
		if ((ft_strnstr(cub[i], "F", 1) || ft_strnstr(cub[i], "F", 1)))
		{
			if (colors)
				free_tab(colors);
			colors = ft_split(cub[i], ',');
			while (colors[j])
			{
				colors[j] = ft_strtrim(colors[j], "F");
				colors[j] = ft_strtrim(colors[j], "C");
				colors[j] = ft_strtrim(colors[j], " ");
				j++;
			}
			printf("colors = \n");
			print_tab(colors);
		}
		i++;
	}
	if (colors)
		free_tab(colors);
	return (0);
}
