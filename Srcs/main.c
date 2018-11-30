/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 14:23:13 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/30 12:19:55 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

#include <arpa/inet.h>

#include <signal.h>

#include <unistd.h>

#include <stdio.h>
#include <netinet/ip_icmp.h>

#include "ft_ping.h"

#include "libft.h"

t_stats	g_stats;

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

void	ft_msgcpy(struct msghdr *dst, struct msghdr *src)
{
	static uint8_t		ctrlDataBuffer[CMSG_SPACE(sizeof(uint8_t))];
	static char			name[255];
	static struct iovec	vec[1];
	static char			vec_data[255];

	vec->iov_base = vec_data;
	vec->iov_len = sizeof(vec_data);
	ft_bzero(dst, sizeof(*dst));
	ft_bzero(name, sizeof(name));
	ft_bzero(vec_data, sizeof(vec_data));
	dst->msg_name = name;
	dst->msg_namelen = sizeof(name);
	dst->msg_iov = vec;
	dst->msg_iovlen = 1;
	dst->msg_control = ctrlDataBuffer;
	dst->msg_controllen = sizeof(ctrlDataBuffer);
	ft_memcpy(dst->msg_name, src->msg_name, src->msg_namelen);
	dst->msg_namelen = src->msg_namelen;
	vec[0].iov_len = src->msg_iov[0].iov_len;
	ft_memcpy(vec[0].iov_base, src->msg_iov[0].iov_base, vec[0].iov_len);
	ft_memcpy(dst->msg_control, src->msg_control, src->msg_controllen);
	dst->msg_controllen = src->msg_controllen;
	dst->msg_flags = src->msg_flags;
}

ssize_t ft_recvmsg(int s, struct msghdr *msg, int flags, uint16_t id)
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

void	print_ping_res(struct timeval tv_end, t_my_msg msg)
{
	float			ping;
	int				ttl;
	t_ping_pckt		in_pckt;
	struct timeval	*tv_start;

	ft_bzero(&in_pckt, sizeof(in_pckt));
	read_msg_data(msg.msg, &ttl, &in_pckt);
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
	if (in_pckt.hdr.type == ICMP_TIME_EXCEEDED)
		printf("Time to live exceeded\n");
	else
		printf("ttl=%d, time=%.1f ms\n", ttl, ping);
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

void	start_print(t_ping_pckt *pckt)
{
	printf("PING %s (%s) ", g_stats.dn, g_stats.ip);
	printf("%zu", sizeof(pckt->msg));
	printf("(%zu) bytes of data.\n", sizeof(*pckt) + sizeof(struct iphdr));
}

int		ft_ping(char *hostname)
{
	struct sockaddr		sout;
	int					s;
	struct s_ping_pckt	pckt;

	if (get_host_addr(hostname, &sout))
		return (1);
	g_stats.ip = get_host_ip(sout);
	if ((s = create_socket(255, 1)) < 0)
	{
		ft_printf("Socket creation failed!\n");
		return (1);
	}
	fill_ping_pckt(&pckt, 1);
	start_print(NULL);
	g_stats.sent = 0;
	g_stats.lost = 0;
	signal(SIGINT, &sigint_handler);
	signal(SIGALRM, &sigint_handler);
	alarm(60);
	while (1)
	{
		single_ping(s, &pckt, &sout);
		sleep(1);
		pckt.hdr.un.echo.sequence++;
	}
	return (0);
}

int		main(int argc, char **argv)
{

	if (argc < 2)
		return (1);
	ft_bzero(&g_stats, sizeof(g_stats));
	ft_ping(argv[1]);
	return (0);
}
