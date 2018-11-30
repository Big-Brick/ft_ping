/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 13:29:00 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/11 13:32:00 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

static unsigned		count_digits(int i)
{
	unsigned	res;
	long		base;

	res = 1;
	base = 10;
	while ((i % base) != i)
	{
		res++;
		base *= 10;
	}
	return (res);
}

static long			my_pow(int value, unsigned power)
{
	long	res;

	res = 1;
	while (power > 0)
	{
		res *= value;
		power--;
	}
	return (res);
}

char				*ft_itoa(int i)
{
	char		*res;
	size_t		ct;
	long		base;

	if (i < 0)
	{
		res = (char*)malloc(sizeof(*res) * (count_digits(i) + 2));
		res[0] = '-';
		ct = 1;
	}
	else
	{
		res = (char*)malloc(sizeof(*res) * (count_digits(i) + 1));
		ct = 0;
	}
	base = my_pow(10, count_digits(i) - 1);
	while (base)
	{
		res[ct++] = '0' + (i / base);
		i = i % base;
		base /= 10;
	}
	res[ct] = 0;
	return (res);
}
