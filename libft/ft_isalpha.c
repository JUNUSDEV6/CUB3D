#include "libft.h"

int	ft_isalpha(int c)
{
	if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)))
		return (1);
	else
		return (0);
}

/*int	main()
	{
		int	a;

		a = 'Z';

		printf("%d", (ft_isalpha(a)));
		printf("%d", (isalpha(a)));
		return(0);
	}*/
