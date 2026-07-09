/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_bfs_apply_rotate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 22:51:28 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/16 22:51:30 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "small_bfs_additions.h"

static void	rotate(int *small_block_x, int x_size)
{
	int	tmp;
	int	i;

	tmp = small_block_x[0];
	i = -1;
	while (++i + 1 < x_size)
		small_block_x[i] = small_block_x[i + 1];
	small_block_x[x_size - 1] = tmp;
}

static void	rev_rotate(int *small_block_x, int x_size)
{
	int	tmp;
	int	i;

	tmp = small_block_x[x_size - 1];
	i = x_size - 1;
	while (i > 0)
	{
		small_block_x[i] = small_block_x[i - 1];
		i--;
	}
	small_block_x[0] = tmp;
}

int	try_apply_rotate_op(t_st *next_state, int op, t_bfs *bfs)
{
	if (op == M_RA && bfs->rest_a == 0 && next_state->a_size >= 2)
		return (rotate(next_state->a, next_state->a_size), 1);
	if (op == M_RB && bfs->rest_b == 0 && next_state->b_size >= 2)
		return (rotate(next_state->b, next_state->b_size), 1);
	if (op == M_RRA && bfs->rest_a == 0 && next_state->a_size >= 2)
		return (rev_rotate(next_state->a, next_state->a_size), 1);
	if (op == M_RRB && bfs->rest_b == 0 && next_state->b_size >= 2)
		return (rev_rotate(next_state->b, next_state->b_size), 1);
	return (0);
}
