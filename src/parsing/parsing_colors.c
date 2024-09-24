#include "library.h"

char	**create_colors_tab(char **cub, int i)
{
	char	**colors;
	char	*temp;
	int		j;

	colors = NULL;
	temp = NULL;
	j = -1;
	colors = ft_split(cub[i], ',');
	if (!colors)
		return (NULL);
	while (colors[++j])
	{
		temp = ft_strtrim(colors[j], "F");
		free (colors[j]);
		colors[j] = ft_strtrim(temp, "C");
		free (temp);
		temp = NULL;
		temp = ft_strtrim(colors[j], " ");
		free (colors[j]);
		colors[j] = ft_strdup(temp);
		free (temp);
		temp = NULL;
	}
	free (temp);
	return (colors);
}

static int	check_colors_values(char **colors)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	while (colors[i])
	{
		value = ft_atoi(colors[i]);
		if (value < 0 || value > 255)
			return (1);
		if (value == 0 && !ft_strchr(colors[i], '0')
			&& ft_strlen(colors[i]) != 1)
			return (1);
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}

int	parsing_colors(char **cub)
{
	int		i;
	char	**colors;

	i = 0;
	colors = NULL;
	while (cub[i] && i < 6)
	{
		if ((ft_strnstr(cub[i], "F", 1) || ft_strnstr(cub[i], "C", 1)))
		{
			if (colors)
				free_tab(colors);
			colors = create_colors_tab(cub, i);
			if (check_colors_values(colors))
			{
				free_tab(colors);
				return (error("Bad colors formatting"));
			}
		}
		i++;
	}
	if (colors)
		free_tab(colors);
	return (0);
}
