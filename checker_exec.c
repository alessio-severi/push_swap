/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvigonz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 17:04:31 by elvigonz          #+#    #+#             */
/*   Updated: 2026/07/06 17:12:04 by elvigonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	str_equals(const char *a, const char *b)
{
	while (*a && *b)
	{
		if (*a != *b)
			return (0);
		a++;
		b++;
	}
	return (*a == '\0' && *b == '\0');
}

int	str_to_opcode(char *s)
{
	if (str_equals(s, "sa"))
		return (OP_SA);
	if (str_equals(s, "sb"))
		return (OP_SB);
	if (str_equals(s, "ss"))
		return (OP_SS);
	if (str_equals(s, "pa"))
		return (OP_PA);
	if (str_equals(s, "pb"))
		return (OP_PB);
	if (str_equals(s, "ra"))
		return (OP_RA);
	if (str_equals(s, "rb"))
		return (OP_RB);
	if (str_equals(s, "rr"))
		return (OP_RR);
	if (str_equals(s, "rra"))
		return (OP_RRA);
	if (str_equals(s, "rrb"))
		return (OP_RRB);
	if (str_equals(s, "rrr"))
		return (OP_RRR);
	return (-1);
}

int	execute_move(t_checker *ck, char *s)
{
	int	i;
	int	op;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	s[i] = '\0';
	op = str_to_opcode(s);
	if (op == -1)
		return (0);
	execute_op(ck, op);
	return (1);
}
