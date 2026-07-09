/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peephole_optimizer_try_cond5.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:07:22 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:07:23 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "peephole_optimizer_additions.h"

int	try_cond5_a(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{5, 1, 0, {OP_PB, OP_SB, OP_PA, OP_PA, OP_RRB, 0},
		3, {OP_RA, OP_PA, OP_RRR, 0, 0, 0}},
	{5, 0, 1, {OP_PA, OP_SA, OP_PB, OP_PB, OP_RRA, 0},
		3, {OP_RB, OP_PB, OP_RRR, 0, 0, 0}},
	{5, 3, 0, {OP_RA, OP_SA, OP_PB, OP_RRA, OP_PB, 0},
		4, {OP_PB, OP_RR, OP_PB, OP_RRR, 0, 0}},
	{5, 0, 3, {OP_RB, OP_SB, OP_PA, OP_RRB, OP_PA, 0},
		4, {OP_PA, OP_RR, OP_PA, OP_RRR, 0, 0}},
	{5, 0, 1, {OP_PA, OP_RB, OP_RB, OP_PB, OP_SA, 0},
		4, {OP_SB, OP_RB, OP_SS, OP_RB, 0, 0}},
	{5, 1, 0, {OP_PB, OP_RA, OP_RA, OP_PA, OP_SB, 0},
		4, {OP_SA, OP_RA, OP_SS, OP_RA, 0, 0}},
	{5, 0, 2, {OP_PA, OP_RRB, OP_PA, OP_RRB, OP_SA, 0},
		4, {OP_RRB, OP_PA, OP_PA, OP_RRB, 0, 0}},
	{5, 2, 0, {OP_PB, OP_RRA, OP_PB, OP_RRA, OP_SB, 0},
		4, {OP_RRA, OP_PB, OP_PB, OP_RRA, 0, 0}},
	{5, 2, 1, {OP_PA, OP_SA, OP_PB, OP_SA, OP_PA, 0},
		4, {OP_RA, OP_PA, OP_SA, OP_RRA, 0, 0}},
	{5, 1, 2, {OP_PB, OP_SB, OP_PA, OP_SB, OP_PB, 0},
		4, {OP_RB, OP_PB, OP_SB, OP_RRB, 0, 0}}
	};

	return (try_table(tp, patterns, 10));
}

int	try_cond5_b(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{5, 2, 0, {OP_RA, OP_SB, OP_PB, OP_PB, OP_RRA, 0},
		4, {OP_SS, OP_PB, OP_SA, OP_PB, 0, 0}},
	{5, 0, 2, {OP_RB, OP_SA, OP_PA, OP_PA, OP_RRB, 0},
		4, {OP_SS, OP_PA, OP_SB, OP_PA, 0, 0}},
	{5, 3, 0, {OP_RB, OP_SA, OP_PB, OP_SA, OP_PA, 0},
		4, {OP_SA, OP_RR, OP_SA, OP_RRA, 0, 0}},
	{5, 0, 3, {OP_RA, OP_SB, OP_PA, OP_SB, OP_PB, 0},
		4, {OP_SB, OP_RR, OP_SB, OP_RRB, 0, 0}},
	{5, 0, 1, {OP_PA, OP_RRB, OP_RRB, OP_PB, OP_SA, 0},
		4, {OP_RRB, OP_SB, OP_RRB, OP_SS, 0, 0}},
	{5, 1, 0, {OP_PB, OP_RRA, OP_RRA, OP_PA, OP_SB, 0},
		4, {OP_RRA, OP_SA, OP_RRA, OP_SS, 0, 0}},
	{5, 0, 2, {OP_PA, OP_RB, OP_PA, OP_SA, OP_PB, 0},
		4, {OP_SB, OP_RB, OP_SB, OP_PA, 0, 0}},
	{5, 2, 0, {OP_PB, OP_RA, OP_PB, OP_SB, OP_PA, 0},
		4, {OP_SA, OP_RA, OP_SA, OP_PB, 0, 0}},
	{5, 0, 3, {OP_PA, OP_SB, OP_PA, OP_SA, OP_PB, 0},
		4, {OP_RB, OP_SB, OP_PA, OP_RRB, 0, 0}},
	{5, 3, 0, {OP_PB, OP_SA, OP_PB, OP_SB, OP_PA, 0},
		4, {OP_RA, OP_SA, OP_PB, OP_RRA, 0, 0}}
	};

	return (try_table(tp, patterns, 10));
}

int	try_cond5_c(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{5, 0, 3, {OP_RRB, OP_PA, OP_SB, OP_PA, OP_SA, 0},
		4, {OP_SB, OP_PA, OP_RRB, OP_PA, 0, 0}},
	{5, 3, 0, {OP_RRA, OP_PB, OP_SA, OP_PB, OP_SB, 0},
		4, {OP_SA, OP_PB, OP_RRA, OP_PB, 0, 0}},
	{5, 0, 2, {OP_SB, OP_PA, OP_SS, OP_RA, OP_PA, 0},
		4, {OP_RR, OP_PA, OP_PA, OP_RRB, 0, 0}},
	{5, 2, 0, {OP_SA, OP_PB, OP_SS, OP_RB, OP_PB, 0},
		4, {OP_RR, OP_PB, OP_PB, OP_RRA, 0, 0}},
	{5, 0, 3, {OP_PA, OP_SB, OP_PB, OP_SB, OP_PA, 0},
		4, {OP_RB, OP_SB, OP_PA, OP_RRB, 0, 0}},
	{5, 3, 0, {OP_PB, OP_SA, OP_PA, OP_SA, OP_PB, 0},
		4, {OP_RA, OP_SA, OP_PB, OP_RRA, 0, 0}},
	{5, 2, 1, {OP_PB, OP_SB, OP_PA, OP_SA, OP_PA, 0},
		4, {OP_RA, OP_PA, OP_SA, OP_RRA, 0, 0}},
	{5, 1, 2, {OP_PA, OP_SA, OP_PB, OP_SB, OP_PB, 0},
		4, {OP_RB, OP_PB, OP_SB, OP_RRB, 0}}
	};

	return (try_table(tp, patterns, 8));
}

int	try_cond5_d(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{5, 0, 2, {OP_SB, OP_PA, OP_SS, OP_PA, OP_SA, 0},
		4, {OP_RR, OP_PA, OP_PA, OP_RRR, 0, 0}},
	{5, 2, 0, {OP_SA, OP_PB, OP_SS, OP_PB, OP_SB, 0},
		4, {OP_RR, OP_PB, OP_PB, OP_RRR, 0, 0}},
	{5, 3, 3, {OP_PB, OP_SA, OP_PA, OP_PA, OP_SB, 0},
		4, {OP_RR, OP_SS, OP_RRR, OP_PA, 0, 0}},
	{5, 3, 3, {OP_PA, OP_SB, OP_PB, OP_PB, OP_SA, 0},
		4, {OP_RR, OP_SS, OP_RRR, OP_PB, 0, 0}},
	{5, 0, 2, {OP_PA, OP_SA, OP_PA, OP_SA, OP_RRB, 0},
		4, {OP_RA, OP_PA, OP_PA, OP_RRR, 0, 0}},
	{5, 2, 0, {OP_PB, OP_SB, OP_PB, OP_SB, OP_RRA, 0},
		4, {OP_RB, OP_PB, OP_PB, OP_RRR, 0, 0}},
	{5, 0, 1, {OP_PA, OP_RB, OP_RB, OP_PB, OP_RA, 0},
		4, {OP_SB, OP_RB, OP_SB, OP_RR, 0, 0}},
	{5, 1, 0, {OP_PB, OP_RA, OP_RA, OP_PA, OP_RB, 0},
		4, {OP_SA, OP_RA, OP_SA, OP_RR, 0, 0}},
	{5, 0, 3, {OP_RRA, OP_SB, OP_PA, OP_SB, OP_PB, 0},
		4, {OP_SB, OP_RB, OP_SB, OP_RRR, 0, 0}},
	{5, 3, 0, {OP_RRB, OP_SA, OP_PB, OP_SA, OP_PA, 0},
		4, {OP_SA, OP_RA, OP_SA, OP_RRR, 0, 0}}
	};

	return (try_table(tp, patterns, 10));
}

int	try_cond5_e(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{5, 0, 1, {OP_RR, OP_PA, OP_RRR, OP_RRB, OP_SB, 0},
		4, {OP_SB, OP_PA, OP_RRB, OP_SS, 0, 0}},
	{5, 1, 0, {OP_RR, OP_PB, OP_RRR, OP_RRA, OP_SA, 0},
		4, {OP_SA, OP_PB, OP_RRA, OP_SS, 0, 0}},
	{5, 2, 0, {OP_RRA, OP_PB, OP_PB, OP_RRA, OP_SB, 0},
		4, {OP_PB, OP_RRA, OP_PB, OP_RRA, 0, 0}},
	{5, 0, 2, {OP_RRB, OP_PA, OP_PA, OP_RRB, OP_SA, 0},
		4, {OP_PA, OP_RRB, OP_PA, OP_RRB, 0, 0}},
	{5, 0, 2, {OP_PA, OP_PA, OP_RRB, OP_SA, OP_PB, 0},
		4, {OP_SB, OP_PA, OP_RRB, OP_SB, 0, 0}},
	{5, 2, 0, {OP_PB, OP_PB, OP_RRA, OP_SB, OP_PA, 0},
		4, {OP_SA, OP_PB, OP_RRA, OP_SA, 0, 0}}
	};

	return (try_table(tp, patterns, 6));
}
