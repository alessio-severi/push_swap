/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:08:40 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:08:41 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	stack_free(t_stack *s)
{
	free(s->data);
	s->data = NULL;
}

static void	oplist_free(t_oplist *ol)
{
	free(ol->ops);
	ol->ops = NULL;
}

void	free_ps(t_ps *ps)
{
	stack_free(&ps->a);
	stack_free(&ps->b);
	oplist_free(&ps->oplist);
}

void	exit_error_ps(t_ps *ps)
{
	free_ps(ps);
	write(2, "Error\n", 6);
	exit(1);
}
