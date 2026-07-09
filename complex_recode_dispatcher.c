/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_recode_dispatcher.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 08:32:47 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/28 08:32:49 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex_additions.h"

t_key	recode_a_top(t_ps *ps, int block_size, t_key old_key, int *pow3)
{
	t_recode	rc;

	rc.data = ps->a.data;
	rc.block_size = block_size;
	rc.expensive_trit = 0;
	rc.pow3 = pow3;
	return (recode_block(&rc, old_key));
}

t_key	recode_b_top(t_ps *ps, int block_size, t_key old_key, int *pow3)
{
	t_recode	rc;

	rc.data = ps->b.data;
	rc.block_size = block_size;
	rc.expensive_trit = 1;
	rc.pow3 = pow3;
	return (recode_block(&rc, old_key));
}

t_key	recode_a_bottom(t_ps *ps, int block_size, t_key old_key, int *pow3)
{
	t_recode	rc;
	int			start;

	start = ps->a.size - block_size;
	rc.data = ps->a.data + start;
	rc.block_size = block_size;
	rc.expensive_trit = 0;
	rc.pow3 = pow3;
	return (recode_block(&rc, old_key));
}

t_key	recode_b_bottom(t_ps *ps, int block_size, t_key old_key, int *pow3)
{
	t_recode	rc;
	int			start;

	start = ps->b.size - block_size;
	rc.data = ps->b.data + start;
	rc.block_size = block_size;
	rc.expensive_trit = 1;
	rc.pow3 = pow3;
	return (recode_block(&rc, old_key));
}
