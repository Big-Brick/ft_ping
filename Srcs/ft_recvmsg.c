/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recvmsg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:30:36 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/30 13:30:36 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

ssize_t		ft_recvmsg(int s, struct msghdr *msg, int flags, uint16_t id)
{
	ssize_t			ret;
	t_ping_pckt		tmp;

	while ((ret = recvmsg(s, msg, flags)) > 0)
	{
		tmp = *(t_ping_pckt*)
				((char*)msg->msg_iov[0].iov_base + sizeof(struct iphdr));
		if (tmp.hdr.un.echo.id == id || tmp.hdr.type == ICMP_TIME_EXCEEDED)
			return (ret);
		prepare_msg_buffer(msg);
	}
	return (ret);
}
