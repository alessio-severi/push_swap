/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peephole_optimizer_try_dispatcher.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:07:46 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:07:47 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "peephole_optimizer_additions.h"

static int	try_safe3(t_peephole *tp)
{
	if (try_safe3_a(tp))
		return (1);
	return (try_safe3_b(tp));
}

static int	try_safe4(t_peephole *tp)
{
	if (try_safe4_a(tp))
		return (1);
	if (try_safe4_b(tp))
		return (1);
	return (try_safe4_c(tp));
}

static int	try_cond4(t_peephole *tp)
{
	if (try_cond4_a(tp))
		return (1);
	if (try_cond4_b(tp))
		return (1);
	return (try_cond4_c(tp));
}

static int	try_cond5(t_peephole *tp)
{
	if (try_cond5_a(tp))
		return (1);
	if (try_cond5_b(tp))
		return (1);
	if (try_cond5_c(tp))
		return (1);
	if (try_cond5_d(tp))
		return (1);
	return (try_cond5_e(tp));
}

int	try_any_pattern(t_peephole *tp)
{
	if (try_cond6(tp))
		return (1);
	if (try_safe5(tp))
		return (1);
	if (try_cond5(tp))
		return (1);
	if (try_safe4(tp))
		return (1);
	if (try_cond4(tp))
		return (1);
	if (try_safe3(tp))
		return (1);
	if (try_cond3(tp))
		return (1);
	if (try_safe2(tp))
		return (1);
	if (try_cond2(tp))
		return (1);
	if (try_neutral_patterns(tp))
		return (1);
	return (try_fusion_patterns(tp));
}
