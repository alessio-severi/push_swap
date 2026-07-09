/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peephole_optimizer_try_safe4.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:08:03 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:08:23 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "peephole_optimizer_additions.h"

int	try_safe5(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{5, 0, 0, {OP_RRR, OP_RRB, OP_RRB, OP_SB, OP_PA, 0},
		4, {OP_RRB, OP_RRR, OP_PA, OP_RRB, 0, 0}},
	{5, 0, 0, {OP_RRR, OP_RRA, OP_RRA, OP_SA, OP_PB, 0},
		4, {OP_RRA, OP_RRR, OP_PB, OP_RRA, 0, 0}},
	{5, 0, 0, {OP_RB, OP_SB, OP_RR, OP_PB, OP_RA, 0},
		4, {OP_RR, OP_SS, OP_RR, OP_PB, 0, 0}},
	{5, 0, 0, {OP_RA, OP_SA, OP_RR, OP_PA, OP_RB, 0},
		4, {OP_RR, OP_SS, OP_RR, OP_PA, 0, 0}},
	{5, 0, 0, {OP_RB, OP_SA, OP_PB, OP_SA, OP_PB, 0},
		4, {OP_RR, OP_PB, OP_PB, OP_RRA, 0, 0}},
	{5, 0, 0, {OP_RA, OP_SB, OP_PA, OP_SB, OP_PA, 0},
		4, {OP_RR, OP_PA, OP_PA, OP_RRB, 0, 0}},
	{5, 0, 0, {OP_SB, OP_RA, OP_PA, OP_SA, OP_RRA, 0},
		4, {OP_RR, OP_PA, OP_SA, OP_RRR, 0, 0}},
	{5, 0, 0, {OP_SA, OP_RB, OP_PB, OP_SB, OP_RRB, 0},
		4, {OP_RR, OP_PB, OP_SB, OP_RRR, 0, 0}},
	{5, 0, 0, {OP_RA, OP_PB, OP_SB, OP_PB, OP_RRA, 0},
		4, {OP_SA, OP_PB, OP_SS, OP_PB, 0, 0}},
	{5, 0, 0, {OP_RB, OP_PA, OP_SA, OP_PA, OP_RRB, 0},
		4, {OP_SB, OP_PA, OP_SS, OP_PA, 0, 0}}
	};

	return (try_table(tp, patterns, 10));
}

int	try_safe4_a(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{4, 0, 0, {OP_RB, OP_SA, OP_PA, OP_RRB, 0, 0},
		2, {OP_SS, OP_PA, 0, 0, 0, 0}},
	{4, 0, 0, {OP_RA, OP_SB, OP_PB, OP_RRA, 0, 0},
		2, {OP_SS, OP_PB, 0, 0, 0, 0}},
	{4, 0, 0, {OP_SB, OP_RB, OP_PB, OP_RA, 0, 0},
		3, {OP_SS, OP_RR, OP_PB, 0, 0, 0}},
	{4, 0, 0, {OP_SA, OP_RA, OP_PA, OP_RB, 0, 0},
		3, {OP_SS, OP_RR, OP_PA, 0, 0, 0}},
	{4, 0, 0, {OP_RB, OP_SB, OP_RR, OP_RA, 0, 0},
		3, {OP_RR, OP_SB, OP_RR, 0, 0, 0}},
	{4, 0, 0, {OP_RA, OP_SA, OP_RR, OP_RB, 0, 0},
		3, {OP_RR, OP_SA, OP_RR, 0, 0, 0}},
	{4, 0, 0, {OP_RB, OP_SA, OP_RR, OP_RA, 0, 0},
		3, {OP_SA, OP_RR, OP_RR, 0, 0, 0}},
	{4, 0, 0, {OP_RA, OP_SB, OP_RR, OP_RB, 0, 0},
		3, {OP_SB, OP_RR, OP_RR, 0, 0, 0}},
	{4, 0, 0, {OP_SA, OP_RA, OP_RA, OP_SB, 0, 0},
		3, {OP_SS, OP_RA, OP_RA, 0, 0, 0}},
	{4, 0, 0, {OP_SB, OP_RB, OP_RB, OP_SA, 0, 0},
		3, {OP_SS, OP_RB, OP_RB, 0, 0, 0}}
	};

	return (try_table(tp, patterns, 10));
}

int	try_safe4_b(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{4, 0, 0, {OP_RR, OP_SA, OP_RRR, OP_RRB, 0, 0},
		3, {OP_RA, OP_SA, OP_RRR, 0, 0, 0}},
	{4, 0, 0, {OP_RR, OP_SB, OP_RRR, OP_RRA, 0, 0},
		3, {OP_RB, OP_SB, OP_RRR, 0, 0, 0}},
	{4, 0, 0, {OP_RRB, OP_SA, OP_RRR, OP_RRA, 0, 0},
		3, {OP_SA, OP_RRR, OP_RRR, 0, 0, 0}},
	{4, 0, 0, {OP_RRA, OP_SB, OP_RRR, OP_RRB, 0, 0},
		3, {OP_SB, OP_RRR, OP_RRR, 0, 0, 0}},
	{4, 0, 0, {OP_RRA, OP_RRR, OP_SA, OP_RRB, 0, 0},
		3, {OP_RRR, OP_RRR, OP_SA, 0, 0, 0}},
	{4, 0, 0, {OP_RRB, OP_RRR, OP_SB, OP_RRA, 0, 0},
		3, {OP_RRR, OP_RRR, OP_SB, 0, 0, 0}},
	{4, 0, 0, {OP_RA, OP_RR, OP_SA, OP_RB, 0, 0},
		3, {OP_RR, OP_RR, OP_SA, 0, 0, 0}},
	{4, 0, 0, {OP_RB, OP_RR, OP_SB, OP_RA, 0, 0},
		3, {OP_RR, OP_RR, OP_SB, 0, 0, 0}},
	{4, 0, 0, {OP_SA, OP_RRA, OP_RRA, OP_SB, 0, 0},
		3, {OP_SS, OP_RRA, OP_RRA, 0, 0, 0}},
	{4, 0, 0, {OP_SB, OP_RRB, OP_RRB, OP_SA, 0, 0},
		3, {OP_SS, OP_RRB, OP_RRB, 0, 0, 0}}
	};

	return (try_table(tp, patterns, 10));
}

int	try_safe4_c(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{4, 0, 0, {OP_RRA, OP_SA, OP_PA, OP_RRB, 0, 0},
		3, {OP_RRR, OP_SS, OP_PA, 0, 0, 0}},
	{4, 0, 0, {OP_RRB, OP_SB, OP_PB, OP_RRA, 0, 0},
		3, {OP_RRR, OP_SS, OP_PB, 0, 0, 0}},
	{4, 0, 0, {OP_RR, OP_SA, OP_RRR, OP_RRB, 0, 0},
		3, {OP_RA, OP_SA, OP_RRR, 0, 0, 0}},
	{4, 0, 0, {OP_RR, OP_SB, OP_RRR, OP_RRA, 0, 0},
		3, {OP_RB, OP_SB, OP_RRR, 0, 0, 0}}
	};

	return (try_table(tp, patterns, 4));
}
