/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_msg_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 12:52:41 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/29 15:13:41 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>

#include <netdb.h>

#include <string.h>
#include <ft_ping.h>

int			read_msg_data(struct msghdr msg, int *ttl, t_ping_pckt *pckt)
{
	struct cmsghdr		*cmsg;

	if (ttl == NULL || pckt == NULL)
		return (1);
	*pckt = *(t_ping_pckt*)((char*)msg.msg_iov[0].iov_base + sizeof(struct iphdr));
	cmsg = CMSG_FIRSTHDR(&msg);
	while (cmsg)
	{
		if (cmsg->cmsg_level == IPPROTO_IP && cmsg->cmsg_type == IP_TTL)
			*ttl = *(int*)CMSG_DATA(cmsg);
		cmsg = CMSG_NXTHDR(&msg, cmsg);
	}
	return (0);
}
