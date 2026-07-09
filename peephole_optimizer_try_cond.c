/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peephole_optimizer_try_cond.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:07:01 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:07:03 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "peephole_optimizer_additions.h"

int	try_cond4_a(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{4, 1, 0, {OP_RRA, OP_PB, OP_RRB, OP_SB, 0, 0},
		2, {OP_RRR, OP_PB, 0, 0, 0, 0}},
	{4, 0, 1, {OP_RRB, OP_PA, OP_RRA, OP_SA, 0, 0},
		2, {OP_RRR, OP_PA, 0, 0, 0, 0}},
	{4, 2, 1, {OP_PA, OP_RA, OP_SA, OP_RRA, 0, 0},
		2, {OP_SA, OP_PA, 0, 0, 0, 0}},
	{4, 1, 2, {OP_PB, OP_RB, OP_SB, OP_RRB, 0, 0},
		2, {OP_SB, OP_PB, 0, 0, 0, 0}},
	{4, 3, 0, {OP_RRA, OP_PB, OP_SA, OP_PA, 0, 0},
		2, {OP_SA, OP_RRA, 0, 0, 0, 0}},
	{4, 0, 3, {OP_RRB, OP_PA, OP_SB, OP_PB, 0, 0},
		2, {OP_SB, OP_RRB, 0, 0, 0, 0}},
	{4, 0, 1, {OP_SA, OP_PA, OP_RRA, OP_SA, 0, 0},
		3, {OP_SA, OP_RRA, OP_PA, 0, 0, 0}},
	{4, 1, 0, {OP_SB, OP_PB, OP_RRB, OP_SB, 0, 0},
		3, {OP_SB, OP_RRB, OP_PB, 0, 0, 0}},
	{4, 0, 2, {OP_PA, OP_PA, OP_RA, OP_PB, 0, 0},
		3, {OP_SB, OP_PA, OP_RA, 0, 0, 0}},
	{4, 2, 0, {OP_PB, OP_PB, OP_RB, OP_PA, 0, 0},
		3, {OP_SA, OP_PB, OP_RB, 0, 0, 0}}
	};

	return (try_table(tp, patterns, 10));
}

int	try_cond4_b(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{4, 0, 2, {OP_PA, OP_RRB, OP_PA, OP_SA, 0, 0},
		3, {OP_RRB, OP_PA, OP_PA, 0, 0, 0}},
	{4, 2, 0, {OP_PB, OP_RRA, OP_PB, OP_SB, 0, 0},
		3, {OP_RRA, OP_PB, OP_PB, 0, 0, 0}},
	{4, 0, 2, {OP_PA, OP_PA, OP_SA, OP_PB, 0, 0},
		2, {OP_SB, OP_PA, 0, 0, 0, 0}},
	{4, 2, 0, {OP_PB, OP_PB, OP_SB, OP_PA, 0, 0},
		2, {OP_SA, OP_PB, 0, 0, 0, 0}},
	{4, 0, 1, {OP_RA, OP_SB, OP_PA, OP_RRA, 0, 0},
		3, {OP_SB, OP_PA, OP_SA, 0, 0, 0}},
	{4, 1, 0, {OP_RB, OP_SA, OP_PB, OP_RRB, 0, 0},
		3, {OP_SA, OP_PB, OP_SB, 0, 0, 0}},
	{4, 3, 0, {OP_PB, OP_SA, OP_PA, OP_SB, 0, 0},
		3, {OP_RA, OP_SS, OP_RRA, 0, 0, 0}},
	{4, 0, 3, {OP_PA, OP_SB, OP_PB, OP_SA, 0, 0},
		3, {OP_RB, OP_SS, OP_RRB, 0, 0, 0}},
	{4, 2, 1, {OP_PA, OP_RA, OP_SA, OP_RRR, 0, 0},
		3, {OP_SA, OP_PA, OP_RRB, 0, 0, 0}},
	{4, 1, 2, {OP_PB, OP_RB, OP_SB, OP_RRR, 0, 0},
		3, {OP_SB, OP_PB, OP_RRA, 0, 0, 0}}
	};

	return (try_table(tp, patterns, 10));
}

int	try_cond4_c(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{4, 0, 1, {OP_RB, OP_PA, OP_SA, OP_RR, 0, 0},
		3, {OP_RR, OP_PA, OP_RB, 0, 0, 0}},
	{4, 1, 0, {OP_RA, OP_PB, OP_SB, OP_RR, 0, 0},
		3, {OP_RR, OP_PB, OP_RA, 0, 0, 0}},
	{4, 0, 1, {OP_RB, OP_PA, OP_SA, OP_RRB, 0, 0},
		3, {OP_SB, OP_PA, OP_SA, 0, 0, 0}},
	{4, 1, 0, {OP_RA, OP_PB, OP_SB, OP_RRA, 0, 0},
		3, {OP_SA, OP_PB, OP_SB, 0, 0, 0}}
	};

	return (try_table(tp, patterns, 4));
}

int	try_cond3(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{3, 0, 1, {OP_PA, OP_RB, OP_PB, 0, 0, 0}, 2, {OP_SB, OP_RB, 0, 0, 0, 0}},
	{3, 1, 0, {OP_PB, OP_RA, OP_PA, 0, 0, 0}, 2, {OP_SA, OP_RA, 0, 0, 0, 0}},
	{3, 0, 1, {OP_PA, OP_RRB, OP_PB, 0, 0, 0}, 2, {OP_RRB, OP_SB, 0, 0, 0, 0}},
	{3, 1, 0, {OP_PB, OP_RRA, OP_PA, 0, 0, 0}, 2, {OP_RRA, OP_SA, 0, 0, 0, 0}},
	{3, 0, 1, {OP_RA, OP_PA, OP_RRA, 0, 0, 0}, 2, {OP_PA, OP_SA, 0, 0, 0, 0}},
	{3, 1, 0, {OP_RA, OP_PB, OP_RRA, 0, 0, 0}, 2, {OP_SA, OP_PB, 0, 0, 0, 0}},
	{3, 0, 1, {OP_RB, OP_PA, OP_RRB, 0, 0, 0}, 2, {OP_SB, OP_PA, 0, 0, 0, 0}},
	{3, 1, 0, {OP_RB, OP_PB, OP_RRB, 0, 0, 0}, 2, {OP_PB, OP_SB, 0, 0, 0, 0}},
	{3, 0, 1, {OP_PA, OP_RRA, OP_SA, 0, 0, 0}, 2, {OP_RRA, OP_PA, 0, 0, 0, 0}},
	{3, 1, 0, {OP_PB, OP_RRB, OP_SB, 0, 0, 0}, 2, {OP_RRB, OP_PB, 0, 0, 0, 0}},
	{3, 0, 1, {OP_RRA, OP_PA, OP_SA, 0, 0, 0}, 2, {OP_PA, OP_RRA, 0, 0, 0, 0}},
	{3, 1, 0, {OP_RRB, OP_PB, OP_SB, 0, 0, 0}, 2, {OP_PB, OP_RRB, 0, 0, 0, 0}}
	};

	return (try_table(tp, patterns, 12));
}

int	try_cond2(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{2, 0, 1, {OP_PA, OP_PB, 0, 0, 0, 0}, 0, {0, 0, 0, 0, 0, 0}},
	{2, 1, 0, {OP_PB, OP_PA, 0, 0, 0, 0}, 0, {0, 0, 0, 0, 0, 0}}
	};

	return (try_table(tp, patterns, 2));
}
