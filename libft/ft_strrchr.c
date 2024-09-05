#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	s_len;
	int	i;

	s_len = ft_strlen(s);
	i = s_len;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}
