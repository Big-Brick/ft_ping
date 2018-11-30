/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 13:56:17 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/15 13:56:24 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char		*buff1;
	const unsigned char		*buff2;
	size_t					i;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	buff1 = s1;
	buff2 = s2;
	i = 0;
	while (i < n)
	{
		if (buff1[i] != buff2[i])
			return (buff1[i] - buff2[i]);
		i++;
	}
	return (0);
}
