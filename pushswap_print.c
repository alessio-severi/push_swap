/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:09:49 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:09:51 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_general.h"

static const char	*op_name(int op)
{
	if (op == OP_PA)
		return ("pa\n");
	if (op == OP_PB)
		return ("pb\n");
	if (op == OP_RA)
		return ("ra\n");
	if (op == OP_RB)
		return ("rb\n");
	if (op == OP_RR)
		return ("rr\n");
	if (op == OP_RRA)
		return ("rra\n");
	if (op == OP_RRB)
		return ("rrb\n");
	if (op == OP_RRR)
		return ("rrr\n");
	if (op == OP_SA)
		return ("sa\n");
	if (op == OP_SB)
		return ("sb\n");
	if (op == OP_SS)
		return ("ss\n");
	return ("");
}

static void	oplist_print(t_ps *ps)
{
	const char	*name;
	int			i;

	i = -1;
	while (++i < ps->oplist.size)
	{
		name = op_name(ps->oplist.ops[i]);
		if (write(1, name, ft_strlen(name)) == -1)
			exit_error_ps(ps);
	}
}

void	pushswap_print(t_ps *ps, t_ps_general psg)
{
	oplist_print(ps);
	if (psg.bench == BENCH_OFF)
		return ;
	bench_disorder_print(ps, psg);
	bench_strategy_print(ps, psg);
	bench_op_print(ps, -1, -1);
	if (write(2, "\n", 1) == -1)
		exit_error_ps(ps);
}
