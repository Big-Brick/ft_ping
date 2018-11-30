/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:40:51 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/15 13:55:56 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*new_t_list_node(void *data, size_t size)
{
	t_list	*res;

	res = (t_list*)malloc(sizeof(*res));
	res->next = NULL;
	res->data = data;
	res->size = size;
	return (res);
}

void		t_list_push_back(t_list **begin, void *data, size_t size)
{
	while (begin && *begin)
		begin = &((*begin)->next);
	if (begin)
		*begin = new_t_list_node(data, size);
}

void		t_list_delete_next_node(t_list **next)
{
	t_list	*tmp;

	if (next && *next)
	{
		tmp = *next;
		*next = (*next)->next;
		free(tmp);
	}
}

void		t_list_clear(t_list **begin)
{
	t_list		*tmp;

	while (begin && *begin)
	{
		tmp = (*begin)->next;
		free((*begin)->data);
		(*begin)->data = NULL;
		(*begin)->size = 0;
		free(*begin);
		(*begin) = tmp;
	}
}
