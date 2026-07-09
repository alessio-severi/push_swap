/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:10:24 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:10:25 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	init_null(t_ps *ps)
{
	ps->a.data = NULL;
	ps->b.data = NULL;
	ps->oplist.ops = NULL;
}

int	stack_init(t_stack *s, int capacity)
{
	s->data = malloc(sizeof(int) * capacity);
	if (!s->data)
		return (0);
	s->size = 0;
	s->capacity = capacity;
	return (1);
}

int	oplist_init(t_oplist *ol, int capacity)
{
	ol->ops = malloc(sizeof(int) * capacity);
	if (!ol->ops)
		return (0);
	ol->size = 0;
	ol->capacity = capacity;
	return (1);
}

static void	oplist_grow(t_ps *ps)
{
	int	*new_ops;
	int	new_capacity;
	int	i;

	new_capacity = ps->oplist.capacity * 2;
	new_ops = malloc(sizeof(int) * new_capacity);
	if (!new_ops)
		exit_error_ps(ps);
	i = -1;
	while (++i < ps->oplist.size)
		new_ops[i] = ps->oplist.ops[i];
	free(ps->oplist.ops);
	ps->oplist.ops = new_ops;
	ps->oplist.capacity = new_capacity;
}

void	oplist_add(t_ps *ps, int op)
{
	if (ps->oplist.size >= ps->oplist.capacity)
		oplist_grow(ps);
	ps->oplist.ops[ps->oplist.size++] = op;
}
