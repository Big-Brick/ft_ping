/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 10:43:50 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/16 09:48:46 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdarg.h>
# include <inttypes.h>
# include <stdlib.h>

# include "list.h"

int		ft_printf(const char *str, ...);

int		ft_atoi(const char *str);

char	*ft_itoa(int i);

void	ft_bzero(void *addr, size_t size);

void	ft_memcpy(void *dst, const void *src, size_t size);

int		ft_strcmp(const char *s1, const char *s2);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strchr(const char *s, int c);

int		ft_strbegins(const char *str, char const *start);

int		ft_strdiff(const char *s1, const char *s2);

int		ft_find_char(char *str, char c);

size_t	ft_strlen(const char *str);

char	*ft_strcpy(char *dst, const char *src);

char	*ft_strncpy(char *dst, const char *src, size_t n);

char	*ft_strdup(const char *s1);

char	*ft_strndup(const char *s1, size_t n);

char	*ft_strsub(const char *s, unsigned int start, size_t len);

char	*ft_strjoin(const char *s1, const char *s2);

char	*ft_multistrjoin(char *strings[], size_t am);

int		ft_count_digits(uintmax_t value, int base);

t_list	*new_t_list_node(void *data, size_t size);

void	t_list_push_back(t_list **begin, void *data, size_t size);

void	t_list_delete_next_node(t_list **next);

void	t_list_clear(t_list **begin);

#endif
