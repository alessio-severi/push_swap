/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_check_block_sorted.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:04:38 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:04:42 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex_additions.h"

int	is_sorted_a_top(t_ps *ps, int block_size)
{
	int	i;
	int	swap;

	swap = 0;
	i = -1;
	while (++i + 1 < block_size)
	{
		if (ps->a.data[i] > ps->a.data[i + 1])
		{
			if (i != 0 || swap)
				return (0);
			swap = 1;
		}
	}
	if (swap && block_size > 2 && ps->a.data[0] > ps->a.data[2])
		return (0);
	if (swap)
		sa(ps);
	return (1);
}

int	is_rev_sorted_b_top(t_ps *ps, int block_size)
{
	int	i;
	int	swap;

	swap = 0;
	i = -1;
	while (++i + 1 < block_size)
	{
		if (ps->b.data[i] < ps->b.data[i + 1])
		{
			if (i != 0 || swap)
				return (0);
			swap = 1;
		}
	}
	if (swap && block_size > 2 && ps->b.data[0] < ps->b.data[2])
		return (0);
	if (swap)
		sb(ps);
	return (1);
}

int	is_sorted_a_bottom(t_ps *ps, int block_size)
{
	int	i;
	int	start;
	int	swap;

	swap = 0;
	start = ps->a.size - block_size;
	i = start - 1;
	while (++i + 1 < ps->a.size)
	{
		if (ps->a.data[i] > ps->a.data[i + 1])
		{
			if (i != start || swap)
				return (0);
			swap = 1;
		}
	}
	if (swap && block_size > 2 && ps->a.data[start] > ps->a.data[start + 2])
		return (0);
	return (1);
}

int	is_rev_sorted_b_bottom(t_ps *ps, int block_size)
{
	int	i;
	int	start;
	int	swap;

	swap = 0;
	start = ps->b.size - block_size;
	i = start - 1;
	while (++i + 1 < ps->b.size)
	{
		if (ps->b.data[i] < ps->b.data[i + 1])
		{
			if (i != start || swap)
				return (0);
			swap = 1;
		}
	}
	if (swap && block_size > 2 && ps->b.data[start] < ps->b.data[start + 2])
		return (0);
	return (1);
}
