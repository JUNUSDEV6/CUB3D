#include "libft.h"

static int	ft_count(int n)
{
	int			count;
	long long	nb;

	count = 0;
	nb = n;
	if (nb < 0)
	{
		nb = nb * -1;
		count++;
	}
	while (nb > 0)
	{
		count++;
		nb = nb / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int			count_nbr;
	char		*str;
	long long	nb;

	nb = n;
	if (nb == 0)
		return (ft_strdup("0"));
	count_nbr = ft_count(n);
	str = malloc(count_nbr + 1 * sizeof(char));
	if (!str)
		return (0);
	str[count_nbr] = '\0';
	if (nb < 0)
		nb = nb * -1;
	while (count_nbr > 0)
	{
		str[count_nbr - 1] = (nb % 10) + 48;
		nb = nb / 10;
		count_nbr--;
	}
	if (str[count_nbr] == '0')
		str[count_nbr] = '-';
	return (str);
}
