/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ping_res.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:33:11 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/30 13:15:16 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>

#include <stdio.h>

#include "ft_ping.h"

#include "libft.h"

void	print_echoreply_res(struct timeval tv_end, t_my_msg msg,
			int ttl, t_ping_pckt in_pckt)
{
	float			ping;
	struct timeval	*tv_start;

	tv_start = (struct timeval*)in_pckt.msg;
	ping = calculate_ping_inter(*tv_start, tv_end);
	if (g_stats.sent == (g_stats.lost + 1))
		init_stats(*tv_start, tv_end);
	else
		update_stats(*tv_start, tv_end);
	if (msg.size >= 0 && (size_t)msg.size >= sizeof(struct iphdr))
		printf("%ld", msg.size - sizeof(struct iphdr));
	else
		printf("0");
	printf(" bytes from");
	if (ft_strcmp(g_stats.dn, g_stats.ip))
		printf(" %s (%s): ", g_stats.dn, g_stats.ip);
	else
		printf(" %s: ", g_stats.ip);
	printf("icmp_seq=%hu ", in_pckt.hdr.un.echo.sequence);
	printf("ttl=%d, time=%.1f ms\n", ttl, ping);
}

void	print_time_exceeded_res(t_my_msg msg, t_ping_pckt in_pckt)
{
	char			name[255];
	t_ping_pckt		*original_pckt;

	if (g_stats.sent > 0)
		g_stats.sent--;
	printf("From");
	if (msg.msg.msg_namelen >= 8)
	{
		ft_bzero(name, 255);
		inet_ntop(AF_INET, msg.msg.msg_name + 4, name, 255);
		printf(" %.255s: ", name);
	}
	original_pckt = (t_ping_pckt*)(in_pckt.msg + sizeof(struct iphdr));
	printf("icmp_seq=%hu ", original_pckt->hdr.un.echo.sequence);
	printf("Time to live exceeded\n");
}

void	print_ping_res(struct timeval tv_end, t_my_msg msg)

{
	int				ttl;
	t_ping_pckt		in_pckt;

	ft_bzero(&in_pckt, sizeof(in_pckt));
	read_msg_data(msg.msg, &ttl, &in_pckt);
	if (in_pckt.hdr.type == ICMP_TIME_EXCEEDED)
		print_time_exceeded_res(msg, in_pckt);
	else
		print_echoreply_res(tv_end, msg, ttl, in_pckt);
}
