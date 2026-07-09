/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_push_to_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 06:16:44 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/17 06:16:48 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simple_additions.h"

static void	absorb_next_from_b(t_ps *ps, int *keep, int *last)
{
	int	next;
	int	rank;

	next = *last + 1;
	while (ps->b.size > 0)
	{
		rank = ps->b.data[0];
		if (rank != next)
			return ;
		pa(ps);
		ra(ps);
		keep[rank] = 1;
		*last = rank;
		next = *last + 1;
	}
}

static int	count_non_lis(int n, int *keep)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < n)
	{
		if (!keep[i])
			count++;
		i++;
	}
	return (count);
}

void	push_non_lis_to_b(t_ps *ps, int n, int *keep)
{
	int	count_to_push;
	int	rank;
	int	last;

	count_to_push = count_non_lis(n, keep);
	last = -1;
	while (count_to_push > 0)
	{
		rank = ps->a.data[0];
		if (keep[rank])
		{
			last = rank;
			ra(ps);
			absorb_next_from_b(ps, keep, &last);
		}
		else
		{
			pb(ps);
			count_to_push--;
		}
	}
}

static int	lis(t_ps *ps, int *incsub_len, int *prev, int n)
{
	int	i;
	int	j;
	int	incsub_best_i;

	i = -1;
	incsub_best_i = 0;
	while (++i < n)
	{
		incsub_len[i] = 1;
		prev[i] = -1;
		j = -1;
		while (++j < i)
		{
			if (ps->a.data[j] < ps->a.data[i]
				&& incsub_len[j] + 1 > incsub_len[i])
			{
				incsub_len[i] = incsub_len[j] + 1;
				prev[i] = j;
			}
		}
		if (incsub_len[i] > incsub_len[incsub_best_i])
			incsub_best_i = i;
	}
	return (incsub_best_i);
}

int	mark_lis(t_ps *ps, int n, int *keep)
{
	int	*incsub_len;
	int	*prev;
	int	incsub_best_i;

	incsub_len = (int *) malloc(sizeof(int) * n);
	prev = (int *) malloc(sizeof(int) * n);
	if (!incsub_len || !prev)
		return (free(incsub_len), free(prev), 0);
	incsub_best_i = lis(ps, incsub_len, prev, n);
	while (incsub_best_i >= 0)
	{
		keep[ps->a.data[incsub_best_i]] = 1;
		incsub_best_i = prev[incsub_best_i];
	}
	return (free(incsub_len), free(prev), 1);
}
