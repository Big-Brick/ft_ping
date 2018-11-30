/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 14:15:32 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/28 12:56:32 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "ft_ping.h"

#include "libft.h"

#include <stdio.h>

#include <math.h>

void	print_pckt_stats(void)
{
	size_t		received;
	float		loss;

	received = g_stats.sent - g_stats.lost;
	loss = (g_stats.lost / (float)g_stats.sent) * 100;
	printf("%zu packets transmitted, %zu received, %01.f%% packet loss\n",
			g_stats.sent, received, loss);
}

void	print_rtt_stats(void)
{
	size_t				received;
	float				min;
	float				avg;
	float				max;

	received = g_stats.sent - g_stats.lost;
	if (received)
	{
		min = calculate_ping(g_stats.min);
		avg = calculate_ping(timeval_scal_div(g_stats.sum, received));
		max = calculate_ping(g_stats.max);
		printf("rtt min/avg/max/mdev = %f/%f/%f ms\n",
				min, avg, max);
	}
}

void	sigint_handler(int signum)
{

	if (signum != SIGINT && signum != SIGALRM && signum != SIGKILL &&
		signum != SIGSTOP)
		exit(1);
	print_pckt_stats();
	print_rtt_stats();
	exit(0);
}

void	print_average(void)
{
	static char flag = 1;
	struct timeval	avg;
	float			avg_ping;

	avg = g_stats.sum;
	avg.tv_usec /= g_stats.sent - g_stats.lost;
	avg.tv_usec += (avg.tv_sec % (g_stats.sent - g_stats.lost)) * 1000000 /
		(g_stats.sent - g_stats.lost);
	avg.tv_sec /= g_stats.sent - g_stats.lost;
	avg_ping = calculate_ping(avg);
	ft_printf("%avg ping %f ms\n", avg_ping);
	if (flag && avg_ping < 5)
	{
		flag = 0;
		print_average();
	}
}
