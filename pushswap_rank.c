/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_rank.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:10:08 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:10:09 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int	has_duplicate(int *data, int n)
{
	int	i;
	int	j;

	i = -1;
	while (++i < n)
	{
		j = i;
		while (++j < n)
		{
			if (data[i] == data[j])
				return (1);
		}
	}
	return (0);
}

static int	next_rank(int *tmp, int i, int n)
{
	int	count;
	int	j;

	count = 0;
	j = -1;
	while (++j < n)
		if (tmp[j] < tmp[i])
			count++;
	return (count);
}

int	add_index(t_ps *ps, int n)
{
	int	i;
	int	*tmp;

	if (has_duplicate(ps->a.data, n))
		return (0);
	tmp = malloc(sizeof(int) * n);
	if (!tmp)
		return (0);
	i = -1;
	while (++i < n)
		tmp[i] = ps->a.data[i];
	i = -1;
	while (++i < n)
		ps->a.data[i] = next_rank(tmp, i, n);
	free(tmp);
	ps->a.size = n;
	return (1);
}

int	check_sorted(t_ps *ps, int n)
{
	int	i;

	i = -1;
	while (++i < n - 1)
		if (ps->a.data[i] >= ps->a.data[i + 1])
			return (0);
	return (1);
}
