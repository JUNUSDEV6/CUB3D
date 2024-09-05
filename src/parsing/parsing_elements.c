#include "library.h"

static int	check_info(char **infos, char *current, char *next)
{
	int		lenght;

	lenght = 0;
	if ((ft_strnstr(current, "NO", 2) || ft_strnstr(current, "SO", 2)
			|| ft_strnstr(current, "WE", 2) || ft_strnstr(current, "EA", 2)
			|| ft_strnstr(current, "F", 1) || ft_strnstr(current, "C", 1))
		&& (ft_strnstr(next, "NO", 2) || ft_strnstr(next, "SO", 2)
			|| ft_strnstr(next, "WE", 2) || ft_strnstr(next, "EA", 2)
			|| ft_strnstr(next, "F", 1) || ft_strnstr(next, "C", 1)))
		return (1);
	while (infos[lenght])
		lenght++;
	if ((ft_strnstr(current, "NO", 2) || ft_strnstr(current, "SO", 2)
			|| ft_strnstr(current, "WE", 2) || ft_strnstr(current, "EA", 2))
		&& (lenght != 2))
		return (1);
	return (0);
}

static int	check_line(char *line)
{
	char	**infos;
	int		i;

	if (!line)
		return (1);
	infos = ft_split(line, ' ');
	i = 0;
	while (infos[i])
	{
		if (infos[i + 1] && check_info(infos, infos[i], infos[i + 1]))
		{
			free_tab(infos);
			return (1);
		}
		i++;
	}
	free_tab(infos);
	return (0);
}

static int	check_elements(char **cub)
{
	int		i;

	if (!cub)
		return (1);
	i = 0;
	while (cub[i])
	{
		if (check_line(cub[i]))
			return (1);
		if (cub[i])
			i++;
	}
	return (0);
}

static int	check_existence(char **cub, char *element)
{
	int		i;
	char	**tab;

	if (!cub || !element)
		return (1);
	i = 0;
	tab = NULL;
	while (cub[i])
	{
		if (tab)
			free_tab(tab);
		tab = ft_split(cub[i], ' ');
		if (!tab)
			return (1);
		if (ft_strnstr(tab[0], element, ft_strlen(element)))
		{
			free_tab(tab);
			return (0);
		}
		if (cub[i])
			i++;
	}
	free_tab(tab);
	return (1);
}

int	missing_element(char **cub)
{
	if (check_elements(cub))
		return (error("Elements in map not written correctly"));
	if (check_existence(cub, "NO"))
		return (error("Missing NO texture"));
	if (check_existence(cub, "SO"))
		return (error("Missing SO texture"));
	if (check_existence(cub, "WE"))
		return (error("Missing WE texture"));
	if (check_existence(cub, "EA"))
		return (error("Missing EA texture"));
	if (check_existence(cub, "F"))
		return (error("Missing F texture"));
	if (check_existence(cub, "C"))
		return (error("Missing C texture"));
	return (0);
}
