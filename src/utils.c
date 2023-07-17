
#include "../Include/philo.h"

t_bool ft_isdigit(int c)
{
	return ((c >= 0x30) & (c <= 0x39));
}

unsigned long	ft_atoi_parse(char *str)
{
	unsigned long	res;

	res = 0;
	if (*str == 0x2D)
		return (-1);
	if (*str == 0x2B)
		str++;
	while (str && *str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		res = res * 0xA + (*(str++) - 0x30);
		if (res > __INT64_MAX__)
			return (-1); 
	}
	return (res);
}