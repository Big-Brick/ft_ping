/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_socket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 12:57:37 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/29 12:03:06 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>

#include <netinet/in.h>

#include <stdio.h>

#include "libft.h"

int		create_socket(int ttl, time_t recv_timeout)
{
	int					res;
	struct timeval		tv_out;
	int					yes;

	if ((res = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		perror("Socket creation failed");
		return (-1);
	}
	if (ttl < 0)
		ttl = 64;
	if (setsockopt(res, SOL_IP, IP_TTL, &ttl, sizeof(ttl)) != 0)
	{
		ft_printf("Setting socket options to TTL failed!\n");
		return (-1);
	}
	tv_out.tv_sec = 5;
	if (recv_timeout != 0)
		tv_out.tv_sec = recv_timeout;
	tv_out.tv_usec = 0;
	if (setsockopt(res, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof(tv_out)))
	{
		ft_printf("Failed to set socket recive timeout!\n");
		return (-1);
	}
	yes = 1;
	if (setsockopt(res, IPPROTO_IP, IP_RECVTTL, &yes, sizeof(yes)))
		return (-1);
	return (res);
}
