/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_rebuild_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 21:40:47 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/19 21:40:48 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "medium_additions.h"

static void	rotate_b_once_to_target(t_ps *ps, int target)
{
	if (dir_to_target_is_forward_b(ps, target))
		rb(ps);
	else
		rrb(ps);
}

static void	complete_target_pair(t_ps *ps, t_rebuild *r)
{
	pa(ps);
	if (ps->b.size >= 2 && ps->b.data[1] == r->target - 2)
		ss(ps);
	else
		sa(ps);
	r->target -= 2;
	r->has_next_target = 0;
}

static int	rebuild_core(t_ps *ps, t_rebuild *r)
{
	if (!r->has_next_target && ps->b.size > 0 && ps->b.data[0] == r->target)
	{
		pa(ps);
		r->target--;
		return (1);
	}
	if (!r->has_next_target && ps->b.size > 0 && ps->b.data[0] == r->target - 1)
	{
		pa(ps);
		r->has_next_target = 1;
		return (1);
	}
	if (ps->b.size > 0 && can_park(ps->b.data[0], r)
		&& (dir_to_target_is_forward_b(ps, r->target)
			|| r->ignore_parking_direction))
	{
		r->parked_bottom = ps->b.data[0];
		pa(ps);
		ra(ps);
		r->parked_count++;
		return (1);
	}
	return (0);
}

void	rebuild_a_with_parking(t_ps *ps, int n)
{
	t_rebuild	r;

	r.target = n - 1;
	r.parked_count = 0;
	r.parked_bottom = -1;
	r.has_next_target = 0;
	r.ignore_parking_direction = n > 100;
	while (ps->b.size > 0 || r.parked_count > 0)
	{
		if (r.has_next_target && ps->b.size > 0 && ps->b.data[0] == r.target)
			complete_target_pair(ps, &r);
		else if (!r.has_next_target && r.parked_count > 0
			&& ps->a.data[ps->a.size - 1] == r.target)
			recover_parked_chain(ps, &r);
		else if (rebuild_core(ps, &r))
			;
		else if (ps->b.size > 0)
			rotate_b_once_to_target(ps, r.target);
	}
}
