/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:53:56 by adzikovs          #+#    #+#             */
/*   Updated: 2017/04/03 14:45:48 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *addr, size_t size)
{
	char	*buf;

	if (addr)
	{
		buf = addr;
		while (size-- != 0)
			buf[size] = 0;
	}
}

void	ft_memcpy(void *dst, const void *src, size_t size)
{
	char			*buff_dst;
	const char		*buff_src;

	if (dst && src)
	{
		buff_dst = (char*)dst;
		buff_src = (const char*)src;
		while (size != 0)
		{
			size--;
			buff_dst[size] = buff_src[size];
		}
	}
}
