/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_bfs_apply_no_rotate.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 22:50:47 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/16 22:50:48 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "small_bfs_additions.h"

static void	push_to_b(t_st *next_state)
{
	int	tmp;
	int	i;

	tmp = next_state->a[0];
	i = -1;
	while (++i + 1 < next_state->a_size)
		next_state->a[i] = next_state->a[i + 1];
	next_state->a_size--;
	i = next_state->b_size;
	while (i > 0)
	{
		next_state->b[i] = next_state->b[i - 1];
		i--;
	}
	next_state->b[0] = tmp;
	next_state->b_size++;
}

static void	push_to_a(t_st *next_state)
{
	int	tmp;
	int	i;

	tmp = next_state->b[0];
	i = -1;
	while (++i + 1 < next_state->b_size)
		next_state->b[i] = next_state->b[i + 1];
	next_state->b_size--;
	i = next_state->a_size;
	while (i > 0)
	{
		next_state->a[i] = next_state->a[i - 1];
		i--;
	}
	next_state->a[0] = tmp;
	next_state->a_size++;
}

int	try_apply_push_op(t_st *next_state, int op)
{
	if (op == M_PB && next_state->a_size > 0)
		return (push_to_b(next_state), 1);
	if (op == M_PA && next_state->b_size > 0)
		return (push_to_a(next_state), 1);
	return (0);
}

static void	sm_swap(int *small_block_x)
{
	int	tmp;

	tmp = small_block_x[0];
	small_block_x[0] = small_block_x[1];
	small_block_x[1] = tmp;
}

int	try_apply_swap_op(t_st *next_state, int op)
{
	if (op == M_SA && next_state->a_size >= 2)
		return (sm_swap(next_state->a), 1);
	if (op == M_SB && next_state->b_size >= 2)
		return (sm_swap(next_state->b), 1);
	if (op == M_SS && (next_state->a_size >= 2 || next_state->b_size >= 2))
	{
		if (next_state->a_size >= 2)
			sm_swap(next_state->a);
		if (next_state->b_size >= 2)
			sm_swap(next_state->b);
		return (1);
	}
	return (0);
}
