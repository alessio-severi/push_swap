/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_ops1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvigonz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:49:16 by elvigonz          #+#    #+#             */
/*   Updated: 2026/07/06 15:04:56 by elvigonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	swap(t_stack *s)
{
	int	temp;

	if (s->size < 2)
		return ;
	temp = s->data[0];
	s->data[0] = s->data[1];
	s->data[1] = temp;
}

static void	push(t_stack *from, t_stack *to)
{
	int	val;
	int	i;

	if (from->size == 0)
		return ;
	val = from->data[0];
	i = 0;
	while (i < from->size - 1)
	{
		from->data[i] = from->data[i + 1];
		i++;
	}
	from->size--;
	i = to->size;
	while (i > 0)
	{
		to->data[i] = to->data[i - 1];
		i--;
	}
	to->data[0] = val;
	to->size++;
}

void	rotate(t_stack *s)
{
	int	temp;
	int	i;

	if (s->size <= 1)
		return ;
	temp = s->data[0];
	i = 0;
	while (i < s->size - 1)
	{
		s->data[i] = s->data[i + 1];
		i++;
	}
	s->data[s->size - 1] = temp;
}

void	reverse_rotate(t_stack *s)
{
	int	temp;
	int	i;

	if (s->size <= 1)
		return ;
	temp = s->data[s->size - 1];
	i = s->size - 1;
	while (i > 0)
	{
		s->data[i] = s->data[i - 1];
		i--;
	}
	s->data[0] = temp;
}

void	execute_op(t_checker *ck, int op)
{
	if (op == OP_SA)
		swap(&ck->a);
	else if (op == OP_SB)
		swap(&ck->b);
	else if (op == OP_SS)
	{
		swap(&ck->a);
		swap(&ck->b);
	}
	else if (op == OP_PA)
		push(&ck->b, &ck->a);
	else if (op == OP_PB)
		push (&ck->a, &ck->b);
	else
		execute_op2(ck, op);
}
