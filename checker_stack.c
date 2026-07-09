/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvigonz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:19:52 by elvigonz          #+#    #+#             */
/*   Updated: 2026/07/06 14:27:19 by elvigonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	stack_init(t_stack *s, int capacity)
{
	s->data = malloc(sizeof(int) * capacity);
	if (!s->data)
		return (0);
	s->size = 0;
	s->capacity = capacity;
	return (1);
}

void	stack_free(t_stack *s)
{
	if (s->data)
		free(s->data);
	s->data = NULL;
	s->size = 0;
	s->capacity = 0;
}

void	init_checker(t_checker *ck)
{
	ck->a.data = NULL;
	ck->b.data = NULL;
}

void	free_ck(t_checker *ck)
{
	stack_free(&ck->a);
	stack_free(&ck->b);
}

int	organize_check(t_checker *ck)
{
	int	i;

	if (ck->b.size != 0)
		return (0);
	i = 0;
	while (i < ck->a.size - 1)
	{
		if (ck->a.data[i] > ck->a.data[i + 1])
			return (0);
		i++;
	}
	return (1);
}
