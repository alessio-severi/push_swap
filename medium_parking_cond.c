/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_parking_cond.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 21:40:09 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/19 21:40:12 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "medium_additions.h"

int	dir_to_target_is_forward_b(t_ps *ps, int target)
{
	int	i;
	int	limit;

	i = -1;
	limit = ps->b.size / 2;
	while (++i <= limit)
		if (ps->b.data[i] == target)
			return (1);
	return (0);
}

int	can_park(int value, t_rebuild *r)
{
	return (value < r->target - 1 && value > r->parked_bottom);
}
