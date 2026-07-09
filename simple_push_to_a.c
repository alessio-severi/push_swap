/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_push_to_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 10:10:01 by aseveri           #+#    #+#             */
/*   Updated: 2026/07/07 10:10:04 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simple_additions.h"

static void	rotate_a_b(t_ps *ps, int i_a, int i_b)
{
	while (i_a > 0 && i_b > 0)
	{
		rr(ps);
		i_a--;
		i_b--;
	}
	while (i_a > 0)
	{
		ra(ps);
		i_a--;
	}
	while (i_b > 0)
	{
		rb(ps);
		i_b--;
	}
}

static void	rev_rotate_a_b(t_ps *ps, int i_a, int i_b)
{
	while (i_a > 0 && i_b > 0)
	{
		rrr(ps);
		i_a--;
		i_b--;
	}
	while (i_a > 0)
	{
		rra(ps);
		i_a--;
	}
	while (i_b > 0)
	{
		rrb(ps);
		i_b--;
	}
}

void	prepare_and_pa(t_ps *ps, int i_b)
{
	int	i_a;
	int	a_rev;
	int	b_rev;

	i_a = insert_pos_a(ps, ps->b.data[i_b]);
	a_rev = (i_a > ps->a.size / 2);
	b_rev = (i_b > ps->b.size / 2);
	if (!a_rev && !b_rev)
		return (rotate_a_b(ps, i_a, i_b), pa(ps));
	if (a_rev && b_rev)
	{
		i_a = ps->a.size - i_a;
		i_b = ps->b.size - i_b;
		return (rev_rotate_a_b(ps, i_a, i_b), pa(ps));
	}
	while (!a_rev && i_a-- > 0)
		ra(ps);
	while (a_rev && i_a++ < ps->a.size)
		rra(ps);
	while (!b_rev && i_b-- > 0)
		rb(ps);
	while (b_rev && i_b++ < ps->b.size)
		rrb(ps);
	pa(ps);
}
