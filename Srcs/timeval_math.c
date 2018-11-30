/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeval_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 11:48:13 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/28 13:05:32 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

struct timeval		timeval_add(struct timeval v1, struct timeval v2)
{
	v1.tv_usec += v2.tv_usec;
	v1.tv_sec += v1.tv_usec / 1000000;
	v1.tv_usec %= 1000000;
	v1.tv_sec += v2.tv_sec;
	return (v1);
}

struct timeval		timeval_scal_div(struct timeval v1, long v2)
{
	struct timeval	res;

	if (v2 == 0)
		return (v1);
	res.tv_sec = v1.tv_sec / v2;
	res.tv_usec = (v1.tv_sec % v2) * 1000000 / v2;
	res.tv_usec += v1.tv_usec / v2;
	return (res);
}
