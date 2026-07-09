/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_lift_bottom.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 08:32:26 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/28 08:32:29 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex_additions.h"

void	lift_a_bottom(t_ps *ps, int block_size)
{
	while (block_size-- > 0)
		rra(ps);
}

void	lift_b_bottom(t_ps *ps, int block_size)
{
	while (block_size-- > 0)
		rrb(ps);
}

void	pa_n(t_ps *ps, int block_size)
{
	while (block_size-- > 0)
		pa(ps);
}
