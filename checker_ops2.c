/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_ops2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvigonz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 17:00:29 by elvigonz          #+#    #+#             */
/*   Updated: 2026/07/06 19:34:33 by elvigonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	execute_op2(t_checker *ck, int op)
{
	if (op == OP_RA)
		rotate(&ck->a);
	else if (op == OP_RB)
		rotate(&ck->b);
	else if (op == OP_RR)
	{
		rotate(&ck->a);
		rotate(&ck->b);
	}
	else if (op == OP_RRA)
		reverse_rotate(&ck->a);
	else if (op == OP_RRB)
		reverse_rotate(&ck->b);
	else if (op == OP_RRR)
	{
		reverse_rotate(&ck->a);
		reverse_rotate(&ck->b);
	}
}
