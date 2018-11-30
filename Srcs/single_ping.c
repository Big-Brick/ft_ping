/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_ping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:32:25 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/30 13:33:24 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

#include <stdio.h>

#include "ft_ping.h"

#include "libft.h"

int		send_ping(int s, t_ping_pckt pckt, struct sockaddr *sout, t_my_msg *msg)
{

	if (sendto(s, &pckt, sizeof(pckt), 0, sout, sizeof(*sout)) <= 0)
	{
		perror("ft_ping: sendmsg");
		return (1);
	}
	g_stats.sent++;
	if ((msg->size = ft_recvmsg(s, &msg->msg, 0, pckt.hdr.un.echo.id)) <= 0)
	{
		perror("ft_ping: recvmsg");
		g_stats.lost++;
		return (1);
	}
	return (0);
}

int		single_ping(int s, t_ping_pckt *pckt,struct sockaddr *sout)
{
	struct timeval		tv_end;
	t_my_msg			msg;

	prepare_msg_buffer(&msg.msg);
	msg.size = 0;
	if (gettimeofday((struct timeval*)pckt->msg, NULL))
	{
		ft_printf("Get time fail!\n");
		return (1);
	}
	pckt->hdr.checksum = 0;
	pckt->hdr.checksum = ip_checksum(pckt, sizeof(*pckt));
	if (send_ping(s, *pckt, sout, &msg))
		return (1);
	if (gettimeofday(&tv_end, NULL))
	{
		ft_printf("Get time fail!\n");
		return (1);
	}
	print_ping_res(tv_end, msg);
	return (0);
}
