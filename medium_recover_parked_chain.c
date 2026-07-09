/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_recover_parked_chain.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 21:40:09 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/19 21:40:12 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "medium_additions.h"

static void	update_parked(t_ps *ps, t_rebuild	*r)
{
	(r->parked_count)--;
	if (r->parked_count > 0)
		r->parked_bottom = ps->a.data[ps->a.size - 1];
	else
		r->parked_bottom = -1;
}

static int	dist_from_top_to_target_b(t_ps *ps, int target)
{
	int	i;

	i = 0;
	while (i < ps->b.size)
	{
		if (ps->b.data[i] == target)
			return (i);
		i++;
	}
	return (-1);
}

static int	parked_chain_rrr_count(t_ps *ps, int chain_len, int future_target)
{
	int	rb_count;
	int	rrb_count;
	int	max_rrr_count;
	int	best_rrr_count;
	int	k;

	rb_count = dist_from_top_to_target_b(ps, future_target);
	if (rb_count == 0)
		return (0);
	rrb_count = ps->b.size - rb_count;
	if (chain_len < rrb_count)
		max_rrr_count = chain_len;
	else
		max_rrr_count = rrb_count;
	best_rrr_count = 0;
	k = 1;
	while (k <= max_rrr_count)
	{
		if (rrb_count - k < rb_count)
			best_rrr_count = k;
		k++;
	}
	return (best_rrr_count);
}

static int	len_parked_chain_at_bottom_a(t_ps *ps, t_rebuild *r)
{
	int	count;
	int	i;

	count = 0;
	i = ps->a.size - 1;
	while (count < r->parked_count && ps->a.data[i] == r->target - count)
	{
		count++;
		i--;
	}
	return (count);
}

void	recover_parked_chain(t_ps *ps, t_rebuild *r)
{
	int	chain_len;
	int	best_rrr_count;

	chain_len = len_parked_chain_at_bottom_a(ps, r);
	best_rrr_count = parked_chain_rrr_count(ps, chain_len,
			r->target - chain_len);
	while (best_rrr_count-- > 0)
	{
		rrr(ps);
		r->target--;
		update_parked(ps, r);
		chain_len--;
	}
	while (chain_len-- > 0)
	{
		rra(ps);
		r->target--;
		update_parked(ps, r);
	}
}
