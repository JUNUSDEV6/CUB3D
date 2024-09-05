#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		size_of_s1;
	int		total_size;
	int		i;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	size_of_s1 = ft_strlen(s1);
	total_size = ft_strlen(s1) + ft_strlen(s2);
	result = calloc(sizeof(char), (total_size + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < size_of_s1)
	{
		result[i] = s1[i];
		i++;
	}
	while (i < total_size)
	{
		result[i] = s2[i - size_of_s1];
		i++;
	}
	free (s1);
	return (result);
}
