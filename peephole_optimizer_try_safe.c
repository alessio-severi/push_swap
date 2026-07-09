/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peephole_optimizer_try_safe.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:08:03 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:08:23 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "peephole_optimizer_additions.h"

int	try_safe3_a(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{3, 0, 0, {OP_RB, OP_SA, OP_RRB, 0, 0, 0},
		1, {OP_SA, 0, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RA, OP_SB, OP_RRA, 0, 0, 0},
		1, {OP_SB, 0, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RRA, OP_SB, OP_RA, 0, 0, 0},
		1, {OP_SB, 0, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RRB, OP_SA, OP_RB, 0, 0, 0},
		1, {OP_SA, 0, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RRA, OP_RRR, OP_RRB, 0, 0, 0},
		2, {OP_RRR, OP_RRR, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RRB, OP_RRR, OP_RRA, 0, 0, 0},
		2, {OP_RRR, OP_RRR, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RB, OP_RR, OP_RA, 0, 0, 0},
		2, {OP_RR, OP_RR, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RA, OP_RR, OP_RB, 0, 0, 0},
		2, {OP_RR, OP_RR, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RRA, OP_SA, OP_PB, 0, 0, 0},
		2, {OP_PB, OP_RRA, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RRB, OP_SB, OP_PA, 0, 0, 0},
		2, {OP_PA, OP_RRB, 0, 0, 0, 0}}
	};

	return (try_table(tp, patterns, 10));
}

int	try_safe3_b(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{3, 0, 0, {OP_RRB, OP_SA, OP_RRA, 0, 0, 0}, 2, {OP_SA, OP_RRR, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RRA, OP_SB, OP_RRB, 0, 0, 0}, 2, {OP_SB, OP_RRR, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RRA, OP_SA, OP_RRB, 0, 0, 0}, 2, {OP_RRR, OP_SA, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RRB, OP_SB, OP_RRA, 0, 0, 0}, 2, {OP_RRR, OP_SB, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RA, OP_SB, OP_RB, 0, 0, 0}, 2, {OP_SB, OP_RR, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RB, OP_SA, OP_RA, 0, 0, 0}, 2, {OP_SA, OP_RR, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RA, OP_SA, OP_RB, 0, 0, 0}, 2, {OP_RR, OP_SA, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RB, OP_SB, OP_RA, 0, 0, 0}, 2, {OP_RR, OP_SB, 0, 0, 0, 0}},
	{3, 0, 0, {OP_SB, OP_RB, OP_SA, 0, 0, 0}, 2, {OP_SS, OP_RB, 0, 0, 0, 0}},
	{3, 0, 0, {OP_SA, OP_RA, OP_SB, 0, 0, 0}, 2, {OP_SS, OP_RA, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RA, OP_PB, OP_RRA, 0, 0, 0}, 2, {OP_SA, OP_PB, 0, 0, 0, 0}},
	{3, 0, 0, {OP_RB, OP_PA, OP_RRB, 0, 0, 0}, 2, {OP_SB, OP_PA, 0, 0, 0, 0}},
	{3, 0, 0, {OP_SA, OP_RRA, OP_SB, 0, 0, 0}, 2, {OP_SS, OP_RRA, 0, 0, 0, 0}},
	{3, 0, 0, {OP_SB, OP_RRB, OP_SA, 0, 0, 0}, 2, {OP_SS, OP_RRB, 0, 0, 0, 0}},
	{3, 0, 0, {OP_SA, OP_RA, OP_SB, 0, 0, 0}, 2, {OP_SS, OP_RA, 0, 0, 0, 0}},
	{3, 0, 0, {OP_SB, OP_RB, OP_SA, 0, 0, 0}, 2, {OP_SS, OP_RB, 0, 0, 0, 0}}
	};

	return (try_table(tp, patterns, 16));
}

int	try_safe2(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{2, 0, 0, {OP_RRB, OP_RR, 0, 0, 0, 0}, 1, {OP_RA, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_RR, OP_RRB, 0, 0, 0, 0}, 1, {OP_RA, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_RRA, OP_RR, 0, 0, 0, 0}, 1, {OP_RB, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_RR, OP_RRA, 0, 0, 0, 0}, 1, {OP_RB, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_RRR, OP_RB, 0, 0, 0, 0}, 1, {OP_RRA, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_RB, OP_RRR, 0, 0, 0, 0}, 1, {OP_RRA, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_RRR, OP_RA, 0, 0, 0, 0}, 1, {OP_RRB, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_RA, OP_RRR, 0, 0, 0, 0}, 1, {OP_RRB, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_SS, OP_SA, 0, 0, 0, 0}, 1, {OP_SB, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_SA, OP_SS, 0, 0, 0, 0}, 1, {OP_SB, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_SS, OP_SB, 0, 0, 0, 0}, 1, {OP_SA, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_SB, OP_SS, 0, 0, 0, 0}, 1, {OP_SA, 0, 0, 0, 0, 0}}
	};

	return (try_table(tp, patterns, 12));
}
