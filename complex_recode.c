/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_recode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 08:32:47 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/28 08:32:49 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex_additions.h"

static void	tail_target(int n, int expensive_trit, int *count)
{
	if (n <= SB_MAX * 2)
	{
		count[2] = n / 2;
		count[expensive_trit] = 0;
		if (!expensive_trit)
			count[1] = (n + 1) / 2;
		else
			count[0] = (n + 1) / 2;
		return ;
	}
	count[2] = SB_MAX;
	if (!expensive_trit)
		count[1] = SB_MAX;
	else
		count[0] = SB_MAX;
	count[expensive_trit] = n - (SB_MAX * 2);
}

/*
**	Build an encoded value whose current ternary digit is selected by count[].
**
**	For tail blocks:
**	0 <= rank < n <= 14, rank ∈ N^*, SB_MAX = 5,
**	count[0] + count[1] + count[2] = n,
**	0 <= count[0] <= SB_MAX, 0 <= count[1] <= SB_MAX, 0 <= count[2] <= SB_MAX
**
**	The returned value is determined case by case:
**	(value / 9) % 3 =
**
**	Case 0:
**	(rank / 9) % 3 = 0 if
**	0 <= rank < count[0] <= 5 < 9 => count[0] > 0,
**
**	Case 1:
**	((9 + rank - count[0]) / 9) % 3 =
**	(1 + ((rank - count[0]) / 9)) % 3 = 1 with
**	((rank - count[0]) / 9) % 3 = 0 if
**	rank - count[0] < count[1] <= 5 and
**	count[0] <= 5 and rank >= count[0] >= 0 =>
**	0 <= rank - count[0] < count[1] <= 5 => count[1] > 0,
**
**	Case 2:
**	(((2 * 9) + rank - count[0] - count[1]) / 9) % 3 =
**	(2 + ((rank - count[0] - count[1]) / 9)) % 3 = 2 with
**	((rank - count[0] - count[1]) / 9) % 3 = 0 if
**	rank - count[0] - count[1] = rank - (n - count[2]) =
**	rank - n + count[2] < n - n + count[2] = count[2] <= 5 =>
**	rank - count[0] - count[1] < count[2] <= 5 and
**	rank >= count[0] + count[1] >= min(count[0]) + min(count[1]) >= 0
**
**	This forces the next split to create bucket sizes count[0], count[1],
**	and count[2], while preserving rank order inside each bucket.
*/
static int	tail_value(int rank, int pow3, int *count)
{
	if (rank < count[0])
		return (rank);
	if (rank < count[0] + count[1])
		return (pow3 + rank - count[0]);
	return ((2 * pow3) + rank - count[0] - count[1]);
}

static t_key	tail_recode_block(t_recode *rc, t_key old_key, int min)
{
	t_key	key;
	int		count[3];
	int		i;
	int		rank;

	tail_target(rc->block_size, rc->expensive_trit, count);
	*rc->pow3 = max_rank_pow3(SB_MAX * 3 - 1);
	i = -1;
	while (++i < rc->block_size)
	{
		rank = decode_rank(rc->data[i], old_key) - min;
		rc->data[i] = tail_value(rank, *rc->pow3, count);
	}
	key.mult = 1;
	key.offset = 0;
	key.initial_encoded_flag = 0;
	return (key);
}

t_key	recode_block(t_recode *rc, t_key old_key)
{
	t_key	new_key;
	int		i;
	int		rank;
	int		min;

	min = min_decode_rank(rc, old_key);
	if (rc->block_size > SB_MAX && rc->block_size < SB_MAX * 3)
		return (tail_recode_block(rc, old_key, min));
	new_key = encoded_key(rc->block_size);
	new_key.initial_encoded_flag = 0;
	i = -1;
	while (++i < rc->block_size)
	{
		rank = decode_rank(rc->data[i], old_key) - min;
		rc->data[i] = rank * new_key.mult + new_key.offset;
	}
	*rc->pow3 = max_encoded_rank_pow3(rc->block_size, new_key);
	return (new_key);
}
