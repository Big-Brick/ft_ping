/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ping_pckt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 13:12:18 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/29 15:08:50 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <netinet/ip_icmp.h>

#include "ft_ping.h"

#include "libft.h"

unsigned short	ip_checksum(void *b, int len)
{
	unsigned short		*buf;
	unsigned int		sum;
	unsigned short 		result;

	buf = b;
	sum = 0;
	while (len > 1)
	{
		sum += *buf++;
		len -= 2;
	}
	if (len == 1)
		sum += *(unsigned char*)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return (result);
}

int				fill_ping_pckt(struct s_ping_pckt *pckt, uint16_t seq)
{
	ft_bzero(pckt, sizeof(*pckt));
	pckt->hdr.type = ICMP_ECHO;
	pckt->hdr.un.echo.id = getpid();
	pckt->hdr.un.echo.sequence = seq;
	ft_bzero(pckt->msg, sizeof(pckt->msg));
	pckt->hdr.checksum = ip_checksum(pckt, sizeof(*pckt));
	return (0);
}
