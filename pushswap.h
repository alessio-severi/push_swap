/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:10:38 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:10:40 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

/* pushswap */
typedef struct s_stack
{
	int		*data;
	int		size;
	int		capacity;
}	t_stack;

typedef struct s_oplist
{
	int			*ops;
	int			size;
	int			capacity;
}	t_oplist;

typedef struct s_ps
{
	t_stack		a;
	t_stack		b;
	t_oplist	oplist;
}	t_ps;

/* op codes */
# define OP_PA	1
# define OP_PB	2
# define OP_RA	3
# define OP_RB	4
# define OP_RR	5
# define OP_RRA	6
# define OP_RRB	7
# define OP_RRR	8
# define OP_SA	9
# define OP_SB	10
# define OP_SS	11

/* pushswap_rank.c */
int			add_index(t_ps *ps, int n);
int			check_sorted(t_ps *ps, int n);

/* pushswap_utils.c */
void		init_null(t_ps *ps);
int			stack_init(t_stack *s, int capacity);
int			oplist_init(t_oplist *ol, int capacity);
void		oplist_add(t_ps *ps, int op);

/* pushswap_free.c */
void		free_ps(t_ps *ps);
void		exit_error_ps(t_ps *ps);

/* pushswap_ops_part1.c */
void		ra(t_ps *ps);
void		rb(t_ps *ps);
void		rr(t_ps *ps);
void		rra(t_ps *ps);
void		rrb(t_ps *ps);

/* pushswap_ops_part2.c */
void		rrr(t_ps *ps);

/* pushswap_ops_part3.c */
void		pa(t_ps *ps);
void		pb(t_ps *ps);
void		sa(t_ps *ps);
void		sb(t_ps *ps);
void		ss(t_ps *ps);

#endif
