/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 22:53:37 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/16 22:53:38 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "small_bfs_additions.h"

static void	small_rank_vals(int *small_rank, int *src, int size)
{
	int	i;
	int	j;
	int	cnt;

	i = -1;
	while (++i < size)
	{
		cnt = 0;
		j = -1;
		while (++j < size)
			if (src[j] < src[i])
				cnt++;
		small_rank[i] = cnt;
	}
}

static void	init_bfs(t_bfs *bfs, t_ps *ps, int from_b)
{
	int	i;

	bfs->idx = 0;
	i = -1;
	while (++i < SN_MAX)
		bfs->visited[i] = 0;
	bfs->count = 1;
	if (from_b)
	{
		bfs->rest_a = ps->a.size;
		bfs->rest_b = ps->b.size - bfs->size;
	}
	else
	{
		bfs->rest_a = ps->a.size - bfs->size;
		bfs->rest_b = ps->b.size;
	}
}

static void	init_node(t_bfs *bfs, int *vals, int from_b)
{
	int	i;

	bfs->nodes[0].state.a_size = 0;
	bfs->nodes[0].state.b_size = 0;
	i = -1;
	while (++i < bfs->size)
	{
		if (from_b)
			bfs->nodes[0].state.b[bfs->nodes[0].state.b_size++] = vals[i];
		else
			bfs->nodes[0].state.a[bfs->nodes[0].state.a_size++] = vals[i];
	}
	bfs->visited[state_code(&bfs->nodes[0].state, bfs->size)] = 1;
	bfs->nodes[0].prev = -1;
	bfs->nodes[0].op = 0;
}

void	small_sort(t_ps *ps, int size, int from_b)
{
	int		vals[SB_MAX];
	t_bfs	bfs;

	if (size > SB_MAX)
		return ;
	bfs.size = size;
	if (from_b)
		small_rank_vals(vals, ps->b.data, size);
	else
		small_rank_vals(vals, ps->a.data, size);
	init_bfs(&bfs, ps, from_b);
	init_node(&bfs, vals, from_b);
	while (bfs.idx < bfs.count)
	{
		if (is_goal(&bfs.nodes[bfs.idx].state, size))
			return (apply_sort(ps, bfs.nodes, bfs.idx));
		adds_child_nodes(&bfs);
		bfs.idx++;
	}
}
