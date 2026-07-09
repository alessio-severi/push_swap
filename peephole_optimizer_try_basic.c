/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peephole_optimizer_try_basic.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:06:35 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:06:39 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "peephole_optimizer_additions.h"

int	try_neutral_patterns(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{2, 0, 0, {OP_RA, OP_RRA, 0, 0, 0, 0}, 0, {0, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_RRA, OP_RA, 0, 0, 0, 0}, 0, {0, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_RB, OP_RRB, 0, 0, 0, 0}, 0, {0, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_RRB, OP_RB, 0, 0, 0, 0}, 0, {0, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_SA, OP_SA, 0, 0, 0, 0}, 0, {0, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_SB, OP_SB, 0, 0, 0, 0}, 0, {0, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_SS, OP_SS, 0, 0, 0, 0}, 0, {0, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_RR, OP_RRR, 0, 0, 0, 0}, 0, {0, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_RRR, OP_RR, 0, 0, 0, 0}, 0, {0, 0, 0, 0, 0, 0}}
	};

	return (try_table(tp, patterns, 9));
}

int	try_fusion_patterns(t_peephole *tp)
{
	const t_pattern	patterns[] = {
	{2, 0, 0, {OP_RA, OP_RB, 0, 0, 0, 0}, 1, {OP_RR, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_RB, OP_RA, 0, 0, 0, 0}, 1, {OP_RR, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_RRA, OP_RRB, 0, 0, 0, 0}, 1, {OP_RRR, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_RRB, OP_RRA, 0, 0, 0, 0}, 1, {OP_RRR, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_SA, OP_SB, 0, 0, 0, 0}, 1, {OP_SS, 0, 0, 0, 0, 0}},
	{2, 0, 0, {OP_SB, OP_SA, 0, 0, 0, 0}, 1, {OP_SS, 0, 0, 0, 0, 0}},
	};

	return (try_table(tp, patterns, 6));
}
