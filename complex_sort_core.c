/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:05:18 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:05:20 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex_additions.h"

void	complex_sort_a_top_core(t_ps *ps, int block_size, int pow3, int *count)
{
	int	i;
	int	digit;

	init_counts(count);
	i = 0;
	while (i++ < block_size)
	{
		digit = trit_value(ps->a.data[0], pow3);
		if (digit == 2 && ++count[2])
			ra(ps);
		else if (digit == 1 && ++count[1])
			pb(ps);
		else
		{
			pb(ps);
			rb(ps);
			count[0]++;
		}
	}
}

void	complex_sort_a_bottom_core(t_ps *ps, int block_size, int pow3,
			int *count)
{
	int	i;
	int	digit;

	init_counts(count);
	i = 0;
	while (i++ < block_size)
	{
		rra(ps);
		digit = trit_value(ps->a.data[0], pow3);
		if (digit == 2 && ++count[2])
			;
		else if (digit == 1 && ++count[1])
			pb(ps);
		else
		{
			pb(ps);
			rb(ps);
			count[0]++;
		}
	}
}

void	complex_sort_b_top_core(t_ps *ps, int block_size, int pow3, int *count)
{
	int	i;
	int	digit;

	init_counts(count);
	i = 0;
	while (i++ < block_size)
	{
		digit = trit_value(ps->b.data[0], pow3);
		if (digit == 2 && ++count[2])
			pa(ps);
		else if (digit == 1)
		{
			pa(ps);
			ra(ps);
			count[1]++;
		}
		else
		{
			rb(ps);
			count[0]++;
		}
	}
}

void	complex_sort_b_bottom_core(t_ps *ps, int block_size, int pow3,
			int *count)
{
	int	i;
	int	digit;

	init_counts(count);
	i = 0;
	while (i++ < block_size)
	{
		rrb(ps);
		digit = trit_value(ps->b.data[0], pow3);
		if (digit == 2 && ++count[2])
			pa(ps);
		else if (digit == 1)
		{
			pa(ps);
			ra(ps);
			count[1]++;
		}
		else
			count[0]++;
	}
}
