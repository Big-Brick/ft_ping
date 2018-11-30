/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_msg_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:28:52 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/30 13:28:52 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>

#include "libft.h"

void	prepare_msg_buffer(struct msghdr *msg)
{
	static uint8_t		ctrlDataBuffer[CMSG_SPACE(sizeof(uint8_t))];
	static char			name[255];
	static struct iovec	vec[1];
	static char			vec_data[255];

	vec->iov_base = vec_data;
	vec->iov_len = sizeof(vec_data);
	ft_bzero(msg, sizeof(*msg));
	ft_bzero(name, sizeof(name));
	ft_bzero(vec_data, sizeof(vec_data));
	msg->msg_name = name;
	msg->msg_namelen = sizeof(name);
	msg->msg_iov = vec;
	msg->msg_iovlen = 1;
	msg->msg_control = ctrlDataBuffer;
	msg->msg_controllen = sizeof(ctrlDataBuffer);
}
