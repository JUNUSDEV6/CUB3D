#include "libft.h"

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (write (1, &s[i], 1) == -1)
			return (-1);
		i++;
	}
	return (0);
}
