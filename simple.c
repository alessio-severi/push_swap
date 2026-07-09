/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 06:16:44 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/17 06:16:48 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simple_additions.h"

static void	rotate_min_top(t_ps *ps)
{
	int	min_i;

	min_i = pos_min_a(ps);
	if (min_i <= ps->a.size / 2)
	{
		while (min_i-- > 0)
			ra(ps);
	}
	else
	{
		min_i = ps->a.size - min_i;
		while (min_i-- > 0)
			rra(ps);
	}
}

int	simple_sort(t_ps *ps, int n)
{
	int	*keep;
	int	i_b;
	int	rank;

	if (n <= SB_MAX)
		return (small_sort(ps, n, 0), 1);
	keep = (int *) malloc(sizeof(int) * n);
	if (!keep)
		return (0);
	rank = 0;
	while (rank < n)
		keep[rank++] = 0;
	if (!mark_lis(ps, n, keep))
		return (free(keep), 0);
	push_non_lis_to_b(ps, n, keep);
	free(keep);
	i_b = 0;
	while (ps->b.size > 0)
	{
		i_b = best_pos_b(ps);
		prepare_and_pa(ps, i_b);
	}
	rotate_min_top(ps);
	return (1);
}
