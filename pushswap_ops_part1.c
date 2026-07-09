/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_ops_part1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:08:59 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:09:01 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	ra(t_ps *ps)
{
	int	tmp;
	int	i;

	if (ps->a.size <= 1)
		return ;
	tmp = ps->a.data[0];
	i = -1;
	while (++i < ps->a.size - 1)
		ps->a.data[i] = ps->a.data[i + 1];
	ps->a.data[ps->a.size - 1] = tmp;
	oplist_add(ps, OP_RA);
}

void	rb(t_ps *ps)
{
	int	tmp;
	int	i;

	if (ps->b.size <= 1)
		return ;
	tmp = ps->b.data[0];
	i = -1;
	while (++i < ps->b.size - 1)
		ps->b.data[i] = ps->b.data[i + 1];
	ps->b.data[ps->b.size - 1] = tmp;
	oplist_add(ps, OP_RB);
}

void	rr(t_ps *ps)
{
	int	tmp;
	int	i;
	int	changed;

	changed = 0;
	if (ps->a.size > 1)
	{
		tmp = ps->a.data[0];
		i = -1;
		while (++i < ps->a.size - 1)
			ps->a.data[i] = ps->a.data[i + 1];
		ps->a.data[ps->a.size - 1] = tmp;
		changed = 1;
	}
	if (ps->b.size > 1)
	{
		tmp = ps->b.data[0];
		i = -1;
		while (++i < ps->b.size - 1)
			ps->b.data[i] = ps->b.data[i + 1];
		ps->b.data[ps->b.size - 1] = tmp;
		changed = 1;
	}
	if (changed)
		oplist_add(ps, OP_RR);
}

void	rra(t_ps *ps)
{
	int	tmp;
	int	i;

	if (ps->a.size <= 1)
		return ;
	tmp = ps->a.data[ps->a.size - 1];
	i = ps->a.size;
	while (--i > 0)
		ps->a.data[i] = ps->a.data[i - 1];
	ps->a.data[0] = tmp;
	oplist_add(ps, OP_RRA);
}

void	rrb(t_ps *ps)
{
	int	tmp;
	int	i;

	if (ps->b.size <= 1)
		return ;
	tmp = ps->b.data[ps->b.size - 1];
	i = ps->b.size;
	while (--i > 0)
		ps->b.data[i] = ps->b.data[i - 1];
	ps->b.data[0] = tmp;
	oplist_add(ps, OP_RRB);
}
