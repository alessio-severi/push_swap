/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 06:16:44 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/19 21:41:03 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "medium_additions.h"

int	ceil_div(int a, int b)
{
	int	result;

	result = a / b;
	if (a % b != 0)
		result++;
	return (result);
}

static int	ft_isqrt(int n)
{
	int	r;

	r = 1;
	while (r <= n / r)
		r++;
	return (r - 1);
}

static int	choose_bucket_count(int n)
{
	int	root;
	int	chunks;

	root = ft_isqrt(n);
	chunks = (int)((0.65 * root / 2.0) + 0.5);
	if (chunks < 2)
		chunks = 2;
	return (chunks);
}

void	medium_sort(t_ps *ps, int n)
{
	int	bucket;
	int	bucket_count;

	if (n <= SB_MAX)
		return (small_sort(ps, n, 0));
	n -= SB_MAX;
	bucket_count = choose_bucket_count(n);
	bucket = -1;
	while (++bucket < bucket_count)
		push_bucket_to_b(ps, n, bucket, bucket_count);
	small_sort(ps, SB_MAX, 0);
	rebuild_a_with_parking(ps, n);
}
