#include "libft.h"

static int	ft_check_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (0);
	start = 0;
	while ((s1[start] != '\0') && (ft_check_set(s1[start], set) == 1))
		start++;
	end = ft_strlen(s1);
	while ((end > start) && (ft_check_set(s1[end - 1], set)))
		end--;
	new_str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!new_str)
		return (0);
	i = 0;
	while (start < end)
	{
		new_str[i] = s1[start];
		i++;
		start++;
	}
	new_str[i] = '\0';
	return (new_str);
}
