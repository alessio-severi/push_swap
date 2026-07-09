/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_ops_part3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:09:30 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 22:05:31 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	pb(t_ps *ps)
{
	int	val;
	int	i;

	if (ps->a.size == 0)
		return ;
	val = ps->a.data[0];
	i = -1;
	while (++i < ps->a.size - 1)
		ps->a.data[i] = ps->a.data[i + 1];
	ps->a.size--;
	i = ps->b.size;
	while (i > 0)
	{
		ps->b.data[i] = ps->b.data[i - 1];
		i--;
	}
	ps->b.data[0] = val;
	ps->b.size++;
	oplist_add(ps, OP_PB);
}

void	pa(t_ps *ps)
{
	int	val;
	int	i;

	if (ps->b.size == 0)
		return ;
	val = ps->b.data[0];
	i = 0;
	while (i < ps->b.size - 1)
	{
		ps->b.data[i] = ps->b.data[i + 1];
		i++;
	}
	ps->b.size--;
	i = ps->a.size;
	while (i > 0)
	{
		ps->a.data[i] = ps->a.data[i - 1];
		i--;
	}
	ps->a.data[0] = val;
	ps->a.size++;
	oplist_add(ps, OP_PA);
}

void	sa(t_ps *ps)
{
	int	tmp;

	if (ps->a.size < 2)
		return ;
	tmp = ps->a.data[0];
	ps->a.data[0] = ps->a.data[1];
	ps->a.data[1] = tmp;
	oplist_add(ps, OP_SA);
}

void	sb(t_ps *ps)
{
	int	tmp;

	if (ps->b.size < 2)
		return ;
	tmp = ps->b.data[0];
	ps->b.data[0] = ps->b.data[1];
	ps->b.data[1] = tmp;
	oplist_add(ps, OP_SB);
}

void	ss(t_ps *ps)
{
	int	tmp;
	int	changed;

	changed = 0;
	if (ps->a.size > 1)
	{
		tmp = ps->a.data[0];
		ps->a.data[0] = ps->a.data[1];
		ps->a.data[1] = tmp;
		changed = 1;
	}
	if (ps->b.size > 1)
	{
		tmp = ps->b.data[0];
		ps->b.data[0] = ps->b.data[1];
		ps->b.data[1] = tmp;
		changed = 1;
	}
	if (changed)
		oplist_add(ps, OP_SS);
}
