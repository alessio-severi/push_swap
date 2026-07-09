/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_bfs_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 06:17:12 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/17 06:17:14 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "small_bfs_additions.h"

static void	small_op(t_ps *ps, int op)
{
	if (op == M_SA)
		sa(ps);
	else if (op == M_SB)
		sb(ps);
	else if (op == M_PB)
		pb(ps);
	else if (op == M_PA)
		pa(ps);
	else if (op == M_SS)
		ss(ps);
	else if (op == M_RA)
		ra(ps);
	else if (op == M_RB)
		rb(ps);
	else if (op == M_RRA)
		rra(ps);
	else if (op == M_RRB)
		rrb(ps);
}

/*
**	The solution is reconstructed by walking vertically through the chain,
**	from the goal node back to the root.
**
**	Each node in this chain, except the root, stores the operation that
**	generated it. Therefore, the number of operations to store is equal
**	to the number of edges in this chain.
**	Since the BFS stores at most SN_MAX distinct nodes, any such chain
**	can contain at most SN_MAX nodes, hence at most SN_MAX - 1 edges.
**
**	This is only a structural upper bound; the actual solution is shorter
**	due to additional constraints of the state graph (for example, the
**	valid operations).
*/
void	apply_sort(t_ps *ps, t_node *nodes, int idx)
{
	int	ops[SN_MAX - 1];
	int	n;

	n = 0;
	while (idx > 0)
	{
		ops[n++] = nodes[idx].op;
		idx = nodes[idx].prev;
	}
	while (n-- > 0)
		small_op(ps, ops[n]);
}

int	is_goal(t_st *state, int size)
{
	int	i;

	if (state->a_size != size || state->b_size != 0)
		return (0);
	i = -1;
	while (++i < size)
		if (state->a[i] != i)
			return (0);
	return (1);
}

void	add_node(t_bfs *bfs, t_st *next_state, int op)
{
	bfs->nodes[bfs->count].state = *next_state;
	bfs->nodes[bfs->count].prev = bfs->idx;
	bfs->nodes[bfs->count].op = op;
	bfs->count++;
}

int	factorial(int n)
{
	int	res;

	res = 1;
	while (n > 1)
		res *= n--;
	return (res);
}
