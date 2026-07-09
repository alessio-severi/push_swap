/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_push_to_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 21:40:29 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/19 21:40:31 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "medium_additions.h"

/*
**	floor(x) = max{m ∈ Z | m <= x} = b	=>
**	floor(x) = b <=> b <= x < b + 1		with x ∈ R, b ∈ Z
**	x = rank * bucket_count / n,
**	b := bucket
**	bucket <= rank * bucket_count / n < bucket + 1 	with rank, bucket ∈ Z	=>
**	bucket * n / bucket_count <= rank < (bucket + 1) * n / bucket_count,
**	but rank ∈ Z,
**	y := bucket * n / bucket_count, z := (bucket + 1) * n / bucket_count
**	it follows that
**	low_rank = min{rank ∈ Z | rank >= y} = ceil(y) 	=>
**	low_rank = ceil(bucket * n / bucket_count),
**	high_rank = max{rank ∈ Z | rank < z} = min{rank ∈ Z | rank >= z} - 1
**	= ceil(z) - 1		=>
**	high_rank = ceil((bucket + 1) * n / bucket_count) - 1.
*/
static int	bucket_mid_rank(int n, int bucket, int bucket_count)
{
	int	low_rank;
	int	high_rank;

	low_rank = ceil_div(bucket * n, bucket_count);
	high_rank = ceil_div((bucket + 1) * n, bucket_count) - 1;
	return ((low_rank + high_rank) / 2);
}

/*
**	Maps a rank from [0, n - 1] to a bucket index
**	in [0, bucket_count - 1].
**	This is equivalent to rank / bucket_size in a proportional
**	bucket partition.
**	Integer division intentionally floors the result, so the
**	last valid rank cannot map to bucket_count.
*/
static int	target_bucket_index_of_rank(int rank, int n, int bucket_count)
{
	int	bucket;

	bucket = (rank * bucket_count) / n;
	return (bucket);
}

static int	is_in_target_bucket(int rank, int n, int current_bucket,
	int bucket_count)
{
	return (target_bucket_index_of_rank(rank, n, bucket_count)
		== current_bucket);
}

static int	remaining_bucket_size_in_a(t_ps *ps, int n, int bucket,
	int bucket_count)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < ps->a.size)
	{
		if (ps->a.data[i] < n
			&& is_in_target_bucket(ps->a.data[i], n, bucket, bucket_count))
			count++;
		i++;
	}
	return (count);
}

void	push_bucket_to_b(t_ps *ps, int n, int bucket, int bucket_count)
{
	int	count;
	int	mid;
	int	rank;

	count = remaining_bucket_size_in_a(ps, n, bucket, bucket_count);
	mid = bucket_mid_rank(n, bucket, bucket_count);
	while (count > 0)
	{
		if (ps->a.data[0] < n
			&& is_in_target_bucket(ps->a.data[0], n, bucket, bucket_count))
		{
			rank = ps->a.data[0];
			pb(ps);
			if (bucket == 0 && rank <= mid)
				rb(ps);
			else if (rank < mid - 2)
				rb(ps);
			count--;
		}
		else
			ra(ps);
	}
}
