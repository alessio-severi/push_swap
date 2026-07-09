/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_ops_part2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:09:30 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:09:31 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	rrr(t_ps *ps)
{
	int	tmp;
	int	i;
	int	changed;

	changed = 0;
	if (ps->a.size > 1)
	{
		tmp = ps->a.data[ps->a.size - 1];
		i = ps->a.size;
		while (--i > 0)
			ps->a.data[i] = ps->a.data[i - 1];
		ps->a.data[0] = tmp;
		changed = 1;
	}
	if (ps->b.size > 1)
	{
		tmp = ps->b.data[ps->b.size - 1];
		i = ps->b.size;
		while (--i > 0)
			ps->b.data[i] = ps->b.data[i - 1];
		ps->b.data[0] = tmp;
		changed = 1;
	}
	if (changed)
		oplist_add(ps, OP_RRR);
}
