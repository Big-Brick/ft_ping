/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 14:00:57 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/28 11:58:41 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int			calculate_diff(
		struct timeval *diff,
		struct timeval start,
		struct timeval end)
{
	diff->tv_sec = end.tv_sec - start.tv_sec;
	diff->tv_usec = end.tv_usec - start.tv_usec;
	while (diff->tv_usec < 0)
	{
		if (diff->tv_sec <= 0)
			return (1);
		diff->tv_sec--;
		diff->tv_usec += 1000000;
	}
	return (0);
}

void		init_stats(struct timeval start, struct timeval end)
{
	struct timeval diff;

	if (calculate_diff(&diff, start, end))
	{
		g_stats.sent = g_stats.lost;
		return ;
	}
	g_stats.min = diff;
	g_stats.sum = diff;
	g_stats.max = diff;
}

void		update_stats(struct timeval start, struct timeval end)
{
	struct timeval diff;

	if (calculate_diff(&diff, start, end))
	{
		if (g_stats.sent > 0)
			g_stats.sent--;
		return ;
	}
	if (diff.tv_sec < g_stats.min.tv_sec ||
		(diff.tv_sec == g_stats.min.tv_sec && diff.tv_usec < g_stats.min.tv_usec))
		g_stats.min = diff;
	g_stats.sum = timeval_add(g_stats.sum, diff);
	if (diff.tv_sec > g_stats.max.tv_sec ||
		(diff.tv_sec == g_stats.max.tv_sec && diff.tv_usec > g_stats.max.tv_usec))
		g_stats.max = diff;
}
