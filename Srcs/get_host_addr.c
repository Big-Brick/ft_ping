/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_host_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 12:38:05 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/29 10:59:51 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "libft.h"

#include "ft_ping.h"

int		get_host_addr(char *hostnanme, struct sockaddr *res)
{
	struct addrinfo		*info;
	struct addrinfo		hints;

	if (hostnanme == NULL || res == NULL)
		return (1);
	ft_bzero(&hints, sizeof(hints));
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	if (getaddrinfo(hostnanme, NULL, &hints, &info))
	{
		ft_printf("Failed to get host addr info!\n");
		return (1);
	}
	if (info)
	{
		*res = *(info->ai_addr);
		if (info->ai_canonname)
			g_stats.dn = ft_strdup(info->ai_canonname);
		freeaddrinfo(info);
		return (0);
	}
	ft_printf("Failed to find suitable socket on host!\n");
	return (1);
}

char	*get_host_ip(struct sockaddr saddr)
{
	struct sockaddr_in	*in;
	char				buff[255];

	ft_bzero(buff, sizeof(*buff) * 255);
	in = (struct sockaddr_in*)&saddr;
	if (inet_ntop(in->sin_family, &(in)->sin_addr, buff, 255) == NULL)
		return (NULL);
	return (ft_strdup(buff));
}
