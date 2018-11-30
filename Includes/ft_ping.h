/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 12:37:18 by adzikovs          #+#    #+#             */
/*   Updated: 2018/11/29 14:59:28 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

#include <netinet/ip_icmp.h>

#define PING_PCKT_SIZE 64

typedef struct		s_stats
{
	struct timeval	min;
	struct timeval	sum;
	struct timeval	max;
	size_t			sent;
	size_t			lost;
	char			*dn;
	char			*ip;
}					t_stats;

extern t_stats		g_stats;

typedef struct		s_ping_pckt
{
	struct icmphdr	hdr;
	char 			msg[PING_PCKT_SIZE - sizeof(struct icmphdr)];
}					t_ping_pckt;

typedef struct		s_my_msg
{
	ssize_t			size;
	struct msghdr	msg;
}					t_my_msg;

int					get_host_addr(char *hostnanme, struct sockaddr *res);

char				*get_host_ip(struct sockaddr saddr);

int					create_socket(int ttl, time_t recv_timeout);

unsigned short		ip_checksum(void *b, int len);

int					fill_ping_pckt(struct s_ping_pckt *pckt, uint16_t seq);

int					read_msg_data(struct msghdr msg, int *ttl, t_ping_pckt *pckt);

void				init_stats(struct timeval start, struct timeval end);

void				update_stats(struct timeval start, struct timeval end);

float				calculate_ping_inter(struct timeval tv_start, struct timeval tv_end);

float				calculate_ping(struct timeval diff);

void				sigint_handler(int signum);

void				print_average(void);

struct timeval		timeval_add(struct timeval v1, struct timeval v2);

struct timeval		timeval_scal_div(struct timeval v1, long v2);

#endif
