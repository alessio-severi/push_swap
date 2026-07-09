/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peephole_optimizer_sizes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:06:12 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:06:14 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "peephole_optimizer_additions.h"

void	peephole_optimizer_init(t_peephole *tp, t_oplist *ol,
	int *ops_tmp, int size)
{
	tp->ol = ol;
	tp->ops_tmp = ops_tmp;
	tp->i = 0;
	tp->j = 0;
	tp->a_size = size;
	tp->b_size = 0;
}

static void	peephole_optimizer_update_sizes(int op, int *a, int *b)
{
	if (op == OP_PA && *b > 0)
	{
		(*a)++;
		(*b)--;
	}
	else if (op == OP_PB && *a > 0)
	{
		(*a)--;
		(*b)++;
	}
}

void	peephole_optimizer_update_sizes_seq(t_peephole *tp, int start)
{
	int	k;

	k = start;
	while (k < tp->j)
	{
		peephole_optimizer_update_sizes(tp->ops_tmp[k],
			&tp->a_size, &tp->b_size);
		k++;
	}
}

void	peephole_optimizer_copy_one(t_peephole *tp)
{
	tp->ops_tmp[tp->j] = tp->ol->ops[tp->i];
	tp->j++;
	peephole_optimizer_update_sizes(tp->ol->ops[tp->i],
		&tp->a_size, &tp->b_size);
	tp->i++;
}

void	peephole_optimizer_copy_tmp_to_ops(t_oplist *ol, int *ops_tmp, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ol->ops[i] = ops_tmp[i];
		i++;
	}
}
