/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 14:23:13 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/30 13:31:51 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>

#include <signal.h>

#include <unistd.h>

#include <stdio.h>
#include <netinet/ip_icmp.h>

#include "ft_ping.h"

#include "libft.h"

t_stats	g_stats;

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
	if ((s = create_socket(3, 1)) < 0)
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
