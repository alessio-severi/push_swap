/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_decode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 08:32:47 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/28 08:32:49 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex_additions.h"

int	decode_rank(int value, t_key key)
{
	return ((value - key.offset) / key.mult);
}

int	min_decode_rank(t_recode *rc, t_key old_key)
{
	int		i;
	int		rank;
	int		min;

	min = decode_rank(rc->data[0], old_key);
	i = 0;
	while (++i < rc->block_size)
	{
		rank = decode_rank(rc->data[i], old_key);
		if (rank < min)
			min = rank;
	}
	return (min);
}
