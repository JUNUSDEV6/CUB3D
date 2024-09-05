#include "library.h"

static int	checking_extension(char *s)
{
	int	i;

	i = ft_strlen(s);
	if ((s[i - 4] == '.') && (s[i - 3] == 'c')
		&& (s[i - 2] == 'u') && (s[i - 1] == 'b'))
		return (0);
	return (1);
}

static int	get_cub_fd(char **argv)
{
	int	fd;

	fd = 0;
	if (argv[1])
	{
		fd = open(argv[1], O_RDONLY);
		if (fd <= 0)
			perror("Error");
	}
	return (fd);
}

static char	**get_cub(int fd)
{
	char	*old_line;
	char	*new_line;
	char	*temp;
	char	**cub;

	old_line = ft_calloc(sizeof(char), 1);
	if (!old_line)
		return (NULL);
	while ((new_line = get_next_line(fd)))
	{
		temp = old_line;
		old_line = ft_strjoin(old_line, new_line);
		free(new_line);
		if (!old_line)
		{
			free(temp);
			return (NULL);
		}
	}
	cub = ft_split(old_line, '\n');
	free(new_line);
	free(old_line);
	return (cub);
}

int	parsing_infos(t_cub *cub)
{
	cub->cub = get_cub(cub->fd_cub);
	if (double_infos(cub->cub) || missing_element(cub->cub))
		return (1);
	if (get_textures(cub) /*|| parsing_colors(cub->cub)*/)
		return (1);
	return (0);
}

int	main_parsing(t_cub *cub, int argc, char **argv)
{
	if (argc != 2)
		return (error("Missing map"));
	if (checking_extension(argv[1]))
		return (error("Wrong_extension"));
	cub->fd_cub = get_cub_fd(argv);
	if (cub->fd_cub <= 0)
		return (1);
	if (parsing_infos(cub))
	{
		printf("Parsing problem\n");
		return (1);
	}
	printf("Valid map ✅\n");
	return (0);
}
