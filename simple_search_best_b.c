/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_search_best_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 10:06:25 by aseveri           #+#    #+#             */
/*   Updated: 2026/07/07 10:06:29 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simple_additions.h"

int	pos_min_a(t_ps *ps)
{
	int	min_i;
	int	i;

	min_i = 0;
	i = 1;
	while (i < ps->a.size)
	{
		if (ps->a.data[i] < ps->a.data[min_i])
			min_i = i;
		i++;
	}
	return (min_i);
}

int	insert_pos_a(t_ps *ps, int rank_b)
{
	int	i;

	i = 0;
	while (i < ps->a.size)
	{
		if (i > 0 && ps->a.data[i - 1] < rank_b
			&& rank_b < ps->a.data[i])
			return (i);
		if (i == 0 && ps->a.data[ps->a.size - 1] < rank_b
			&& rank_b < ps->a.data[i])
			return (i);
		i++;
	}
	return (pos_min_a(ps));
}

static int	rot_cost(int i, int size)
{
	if (i <= size / 2)
		return (i);
	return (size - i);
}

static int	move_cost(t_ps *ps, int i_b)
{
	int	i_a;
	int	cost_a;
	int	cost_b;

	i_a = insert_pos_a(ps, ps->b.data[i_b]);
	cost_a = rot_cost(i_a, ps->a.size);
	cost_b = rot_cost(i_b, ps->b.size);
	if ((i_a <= ps->a.size / 2) == (i_b <= ps->b.size / 2))
	{
		if (cost_a > cost_b)
			return (cost_a + 1);
		return (cost_b + 1);
	}
	return (cost_a + cost_b + 1);
}

int	best_pos_b(t_ps *ps)
{
	int	best_i_b;
	int	best_cost;
	int	cost;
	int	i;

	best_i_b = 0;
	best_cost = move_cost(ps, 0);
	i = 1;
	while (i < ps->b.size)
	{
		cost = move_cost(ps, i);
		if (cost < best_cost)
		{
			best_i_b = i;
			best_cost = cost;
		}
		i++;
	}
	return (best_i_b);
}
