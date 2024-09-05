#include "libft.h"

void	*ft_bzero(void *str, size_t n)
{
	unsigned char	*string;
	size_t			i;

	i = 0;
	string = (unsigned char *)str;
	while (i < n)
	{
		string[i] = 0;
		i++;
	}
	str = string;
	return (str);
}
