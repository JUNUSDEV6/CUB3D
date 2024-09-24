#include "library.h"

static int	is_element(char **tab)
{
	if (ft_strnstr(tab[0], "NO", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "SO", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "WE", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "EA", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "F", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "C", ft_strlen(tab[0])))
		return (1);
	return (0);
}

int	floating_elements(char **cub)
{
	int		i;
	char	**tab;

	if (!cub)
		return (1);
	i = 0;
	tab = NULL;
	while (cub[i] && i < 6)
	{
		if (tab)
			free_tab(tab);
		tab = ft_split(cub[i], ' ');
		if (!tab)
			return (1);
		if (!is_element(tab))
		{
			free_tab(tab);
			return (error("Wrong elements in file"));
		}
		if (cub[i])
			i++;
	}
	free_tab(tab);
	return (0);
}
