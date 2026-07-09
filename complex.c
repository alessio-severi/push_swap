/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:05:18 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:05:20 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex_additions.h"

void	complex_sort_a_top(t_ps *ps, int block_size, int pow3, t_key key)
{
	int	count[3];

	if (block_size <= 1 || is_sorted_a_top(ps, block_size))
		return ;
	if (block_size <= SB_MAX)
		return (small_sort(ps, block_size, 0));
	if (!key.initial_encoded_flag || !key.initial_encoded_flag--)
		key = recode_a_top(ps, block_size, key, &pow3);
	complex_sort_a_top_core(ps, block_size, pow3, count);
	if (count[2] < ps->a.size)
		complex_sort_a_bottom(ps, count[2], pow3, key);
	else
		complex_sort_a_top(ps, count[2], pow3, key);
	complex_sort_b_top(ps, count[1], next_pow3(pow3), key);
	if (count[0] < ps->b.size)
		return (complex_sort_b_bottom(ps, count[0], pow3, key));
	complex_sort_b_top(ps, count[0], pow3, key);
}

void	complex_sort_a_bottom(t_ps *ps, int block_size, int pow3, t_key key)
{
	int	count[3];

	if (block_size == 1 || is_sorted_a_bottom(ps, block_size))
	{
		lift_a_bottom(ps, block_size);
		if (block_size > 1 && ps->a.data[0] > ps->a.data[1])
			sa(ps);
		return ;
	}
	if (block_size <= SB_MAX)
		return (lift_a_bottom(ps, block_size), small_sort(ps, block_size, 0));
	key = recode_a_bottom(ps, block_size, key, &pow3);
	complex_sort_a_bottom_core(ps, block_size, pow3, count);
	complex_sort_a_top(ps, count[2], next_pow3(pow3), key);
	complex_sort_b_top(ps, count[1], next_pow3(pow3), key);
	if (count[0] < ps->b.size)
		return (complex_sort_b_bottom(ps, count[0], pow3, key));
	complex_sort_b_top(ps, count[0], pow3, key);
}

void	complex_sort_b_top(t_ps *ps, int block_size, int pow3, t_key key)
{
	int	count[3];

	if (block_size == 0)
		return ;
	if (block_size == 1 || is_rev_sorted_b_top(ps, block_size))
		return (pa_n(ps, block_size));
	if (block_size <= SB_MAX)
		return (small_sort(ps, block_size, 1));
	key = recode_b_top(ps, block_size, key, &pow3);
	complex_sort_b_top_core(ps, block_size, pow3, count);
	complex_sort_a_top(ps, count[2], next_pow3(pow3), key);
	if (count[1] < ps->a.size)
		complex_sort_a_bottom(ps, count[1], pow3, key);
	else
		complex_sort_a_top(ps, count[1], pow3, key);
	if (count[0] < ps->b.size)
		return (complex_sort_b_bottom(ps, count[0], pow3, key));
	complex_sort_b_top(ps, count[0], pow3, key);
}

void	complex_sort_b_bottom(t_ps *ps, int block_size, int pow3, t_key key)
{
	int	count[3];

	if (block_size == 0)
		return ;
	if (block_size == 1 || is_rev_sorted_b_bottom(ps, block_size))
	{
		lift_b_bottom(ps, block_size);
		if (block_size > 1 && ps->b.data[0] < ps->b.data[1])
			sb(ps);
		return (pa_n(ps, block_size));
	}
	if (block_size <= SB_MAX)
		return (lift_b_bottom(ps, block_size), small_sort(ps, block_size, 1));
	key = recode_b_bottom(ps, block_size, key, &pow3);
	complex_sort_b_bottom_core(ps, block_size, pow3, count);
	complex_sort_a_top(ps, count[2], next_pow3(pow3), key);
	if (count[1] < ps->a.size)
		complex_sort_a_bottom(ps, count[1], pow3, key);
	else
		complex_sort_a_top(ps, count[1], pow3, key);
	complex_sort_b_top(ps, count[0], next_pow3(pow3), key);
}

void	complex_sort(t_ps *ps, int n)
{
	t_key	key;
	int		i;

	key = encoded_key(n);
	i = -1;
	while (++i < n)
		ps->a.data[i] = ps->a.data[i] * key.mult + key.offset;
	complex_sort_a_top(ps, n, max_encoded_rank_pow3(n, key), key);
}
