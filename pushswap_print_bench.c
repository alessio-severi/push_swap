/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_print_bench.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:09:49 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:09:51 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_general.h"

static void	cnt_op(t_oplist	oplist, int *cnt_ops, int i)
{
	while (++i < oplist.size)
	{
		if (oplist.ops[i] == OP_PA)
			cnt_ops[OP_PA - 1]++;
		else if (oplist.ops[i] == OP_PB)
			cnt_ops[OP_PB - 1]++;
		else if (oplist.ops[i] == OP_RA)
			cnt_ops[OP_RA - 1]++;
		else if (oplist.ops[i] == OP_RB)
			cnt_ops[OP_RB - 1]++;
		else if (oplist.ops[i] == OP_RR)
			cnt_ops[OP_RR - 1]++;
		else if (oplist.ops[i] == OP_RRA)
			cnt_ops[OP_RRA - 1]++;
		else if (oplist.ops[i] == OP_RRB)
			cnt_ops[OP_RRB - 1]++;
		else if (oplist.ops[i] == OP_RRR)
			cnt_ops[OP_RRR - 1]++;
		else if (oplist.ops[i] == OP_SA)
			cnt_ops[OP_SA - 1]++;
		else if (oplist.ops[i] == OP_SB)
			cnt_ops[OP_SB - 1]++;
		else if (oplist.ops[i] == OP_SS)
			cnt_ops[OP_SS - 1]++;
	}
}

void	bench_op_print(t_ps *ps, int i, int j)
{
	int			cnt_ops[OP_SS];
	const char	*oplist_name_part[] = {"  pa:  ", "  pb:  ", "\n[bench] ra:  ",
		"  rb:  ", "  rr:  ", "  rra:  ", "  rrb:  ", "  rrr:  ",
		"\n[bench] sa:  ", "  sb:  ", "  ss:  "};

	if (write(2, "\n[bench] total_ops:  ", 21) == -1)
		exit_error_ps(ps);
	ft_putnbr_fd_ctrl(ps, ps->oplist.size, 2);
	while (++i < OP_SS)
		cnt_ops[i] = 0;
	cnt_op(ps->oplist, cnt_ops, j);
	i = OP_SA - 1;
	while (i < OP_SS)
	{
		if (write(2, oplist_name_part[i], ft_strlen(oplist_name_part[i])) == -1)
			exit_error_ps(ps);
		ft_putnbr_fd_ctrl(ps, cnt_ops[i++], 2);
	}
	i = OP_PA - 1;
	while (i < OP_RRR)
	{
		if (write(2, oplist_name_part[i], ft_strlen(oplist_name_part[i])) == -1)
			exit_error_ps(ps);
		ft_putnbr_fd_ctrl(ps, cnt_ops[i++], 2);
	}
}

void	bench_strategy_print(t_ps *ps, t_ps_general psg)
{
	if (psg.strategy == COMPLEX_STRATEGY)
		if (write(2, "\n[bench] strategy:  Complex / O(n log n)", 40) == -1)
			exit_error_ps(ps);
	if (psg.strategy == MEDIUM_STRATEGY)
		if (write(2, "\n[bench] strategy:  Medium / O(n √n)", 38) == -1)
			exit_error_ps(ps);
	if (psg.strategy == SIMPLE_STRATEGY)
		if (write(2, "\n[bench] strategy:  Simple / O(n²)", 35) == -1)
			exit_error_ps(ps);
	if (psg.strategy == ADAPTIVE_STRATEGY)
	{
		if (psg.disorder >= 0.5)
			if (write(2, "\n[bench] strategy:  Adaptive / O(n log n)",
					41) == -1)
				exit_error_ps(ps);
		if (psg.disorder >= 0.2 && psg.disorder < 0.5)
			if (write(2, "\n[bench] strategy:  Adaptive / O(n √n)", 40) == -1)
				exit_error_ps(ps);
		if (psg.disorder < 0.2)
			if (write(2, "\n[bench] strategy:  Adaptive / O(n²)", 37) == -1)
				exit_error_ps(ps);
	}
}

void	bench_disorder_print(t_ps *ps, t_ps_general psg)
{
	int	integer;
	int	decimals;

	integer = (int)(psg.disorder * 100);
	decimals = (int)(psg.disorder * 10000 + 0.5) - integer * 100;
	if (write(2, "[bench] disorder:  ", 19) == -1)
		exit_error_ps(ps);
	ft_putnbr_fd_ctrl(ps, integer, 2);
	if (write(2, ".", 1) == -1)
		exit_error_ps(ps);
	ft_putnbr_fd_ctrl(ps, decimals, 2);
	if (!decimals)
		if (write(2, "0", 1) == -1)
			exit_error_ps(ps);
	if (write(2, "%", 1) == -1)
		exit_error_ps(ps);
}
