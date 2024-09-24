#include "library.h"


static int check_position(int position)
{
	if (position > 1)
		return (error("Multiple initial position found in map"));
	if (position == 0)
		return (error("Missing initial position"));
	return (0);
}

static int	check_map_elements(char **map)
{
	int	i;
	int	j;
	int	position;

	i = 0;
	position = 0;
	while (map[i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' '
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W'
				&& map[i][j] != 'E')
				return (error("Wrong elements found in map"));
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
			|| map[i][j] == 'E')
				position++;
		}
		if (map[i])
			i++;
	}
	if (check_position(position))
		return (1);
	return (0);
}

int	map_closed(char **map, int i, int j, int max_length)
{
	int			max_width;
	static int	iteration;

	max_width = 0;
	iteration += 1;
	if (iteration > 50000)
		return (iteration);
	if (i < 0 || i >= max_length)
		return (1);
	while (map[i][max_width])
		max_width++;
	if (j < 0 || j >= max_width || map[i][j] == ' ')
		return (1);
	if (map[i][j] == '1' || !map[i][j])
		return (0);
	map[i][j] = '1';
	if (map_closed(map, i - 1, j, max_length))
		return (iteration);
	if (map_closed(map, i + 1, j, max_length))
		return (iteration);
	if (map_closed(map, i, j - 1, max_length))
		return (iteration);
	if (map_closed(map, i, j + 1, max_length))
		return (iteration);
	return (0);
}

int	check_map(t_cub *cub, char **map, int length)
{
	int	ret;

	ret = 0;
	if (check_map_elements(map))
		return (1);
	ret = map_closed(map, cub->start_i, cub->start_j, length);
	if (ret)
	{
		if (ret > 50000)
			return (error("Map too big, please retry with a smaller map"));
		else
			return (error("Map not closed"));
	}
	return (0);
}

