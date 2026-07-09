/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peephole_optimizer_try_cond6.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:07:22 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:07:23 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "peephole_optimizer_additions.h"

int	try_cond6(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{6, 2, 1, {OP_PA, OP_RA, OP_SA, OP_RRA, OP_RRA, OP_SA},
		3, {OP_SA, OP_RRA, OP_PA, 0, 0, 0}},
	{6, 1, 2, {OP_PB, OP_RB, OP_SB, OP_RRB, OP_RRB, OP_SB},
		3, {OP_SB, OP_RRB, OP_PB, 0, 0, 0}},
	{6, 1, 0, {OP_PB, OP_RRA, OP_RRA, OP_PA, OP_RRB, OP_RRB},
		4, {OP_RRR, OP_SA, OP_RRR, OP_SA, 0, 0}},
	{6, 0, 1, {OP_PA, OP_RRB, OP_RRB, OP_PB, OP_RRA, OP_RRA},
		4, {OP_RRR, OP_SB, OP_RRR, OP_SB, 0, 0}},
	{6, 1, 0, {OP_PB, OP_RA, OP_RA, OP_PA, OP_RB, OP_RB},
		4, {OP_SA, OP_RR, OP_SA, OP_RR, 0, 0}},
	{6, 0, 1, {OP_PA, OP_RB, OP_RB, OP_PB, OP_RA, OP_RA},
		4, {OP_SB, OP_RR, OP_SB, OP_RR, 0, 0}},
	{6, 4, 0, {OP_RRA, OP_RRA, OP_PB, OP_PB, OP_SA, OP_PA},
		4, {OP_SA, OP_RRA, OP_RRA, OP_PB, 0, 0}},
	{6, 0, 4, {OP_RRB, OP_RRB, OP_PA, OP_PA, OP_SB, OP_PB},
		4, {OP_SB, OP_RRB, OP_RRB, OP_PA, 0, 0}},
	{6, 4, 0, {OP_RRA, OP_PB, OP_RRA, OP_PB, OP_SS, OP_PA},
		4, {OP_SA, OP_RRA, OP_RRA, OP_PB, 0, 0}},
	{6, 0, 4, {OP_RRB, OP_PA, OP_RRB, OP_PA, OP_SS, OP_PB},
		4, {OP_SB, OP_RRB, OP_RRB, OP_PA, 0, 0}}
	};

	return (try_table(tp, patterns, 10));
}
