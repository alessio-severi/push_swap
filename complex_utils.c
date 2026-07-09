/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:04:59 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:05:01 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex_additions.h"

int	next_pow3(int pow3)
{
	if (pow3 <= 1)
		return (0);
	return (pow3 / 3);
}

int	trit_value(int value, int pow3)
{
	if (pow3 <= 0)
		return (0);
	return ((value / pow3) % 3);
}

void	init_counts(int *count)
{
	count[0] = 0;
	count[1] = 0;
	count[2] = 0;
}

int	max_encoded_rank_pow3(int n, t_key key)
{
	int	max_key;
	int	pow3;

	max_key = (n - 1) * key.mult + key.offset;
	pow3 = 1;
	while (pow3 <= max_key / 3)
		pow3 *= 3;
	return (pow3);
}

int	max_rank_pow3(int n)
{
	int	pow3;

	pow3 = 1;
	n--;
	while (pow3 <= n / 3)
		pow3 *= 3;
	return (pow3);
}
