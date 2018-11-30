/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 14:25:32 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/28 13:09:46 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys/time.h"

float calculate_ping_inter(struct timeval tv_start, struct timeval tv_end)
{
	float	res;

	res = ((tv_end.tv_sec - tv_start.tv_sec) * 1000 +
			(tv_end.tv_usec - tv_start.tv_usec) / (float)1000);
	return (res);
}

float calculate_ping(struct timeval diff)
{
	float	res;

	res = (diff.tv_sec * 1000 + diff.tv_usec / (float)1000);
	return (res);
}
