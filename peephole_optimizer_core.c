/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peephole_optimizer_core.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:05:54 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:05:57 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "peephole_optimizer_additions.h"

static void	add_pattern(t_peephole *tp, const t_pattern *p)
{
	int	k;

	k = 0;
	while (k < p->out_len)
	{
		tp->ops_tmp[tp->j] = p->out[k];
		tp->j++;
		k++;
	}
	tp->i += p->len;
}

static int	pattern_matches(t_peephole *tp, const t_pattern *p)
{
	int	k;

	if (tp->i + p->len > tp->ol->size)
		return (0);
	if (tp->a_size < p->min_size_a || tp->b_size < p->min_size_b)
		return (0);
	k = 0;
	while (k < p->len)
	{
		if (tp->ol->ops[tp->i + k] != p->in[k])
			return (0);
		k++;
	}
	return (1);
}

int	try_table(t_peephole *tp, const t_pattern *patterns, int count)
{
	int	k;

	k = 0;
	while (k < count)
	{
		if (pattern_matches(tp, &patterns[k]))
		{
			add_pattern(tp, &patterns[k]);
			return (1);
		}
		k++;
	}
	return (0);
}

static int	peephole_optimizer_pass(t_oplist *ol,
	int *ops_tpp, int initial_a_size)
{
	t_peephole		tp;
	int				j_start;
	int				changed;

	peephole_optimizer_init(&tp, ol, ops_tpp, initial_a_size);
	changed = 0;
	while (tp.i < ol->size)
	{
		j_start = tp.j;
		if (try_any_pattern(&tp))
		{
			peephole_optimizer_update_sizes_seq(&tp, j_start);
			changed = 1;
		}
		else
			peephole_optimizer_copy_one(&tp);
	}
	ol->size = tp.j;
	peephole_optimizer_copy_tmp_to_ops(ol, ops_tpp, tp.j);
	return (changed);
}

int	oplist_peephole_optimizer(t_oplist *ol, int initial_a_size)
{
	int	*ops_tpp;
	int	pass;

	ops_tpp = malloc(sizeof(int) * ol->capacity);
	if (!ops_tpp)
		return (0);
	pass = 0;
	while (pass < 64 && peephole_optimizer_pass(ol, ops_tpp, initial_a_size))
		pass++;
	free(ops_tpp);
	return (1);
}
