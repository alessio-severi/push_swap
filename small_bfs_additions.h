/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_bfs_additions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 22:50:29 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/19 21:36:54 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SMALL_BFS_ADDITIONS_H
# define SMALL_BFS_ADDITIONS_H

# include "pushswap.h"

# define SB_MAX	5

/*
**	Uno stato associato ad un nodo è:
**	una certa distribuzione degli n elementi tra A e B,
**	con un certo ordine in A e un certo ordine in B.
**	Supponiamo che A contenga k elementi, allora B contiene n - k elementi
**	dato che lo small sort lavora su massimo n = SB_MAX = 5 elementi.
**	Per costruzione il massimo numero di nodi è il massimo numero di stati
**	in quanto ad ogni nodo è associato uno e un solo stato distinto:
**	un nodo nuovo nasce solo per uno stato nuovo e distinto.
**
**	Poiché esistono k! stati diversi associati ad A, equivalentemente,
**	k! modi per ordinare k elementi distinti in A presi k alla volta, ossia:
**	P(k) = k! per un fissato k.
**	Analogamente, esistono (n - k)! stati diversi associati a B,
**	equivalentemente, (n - k)! modi per ordinare n - k elementi distinti in B
**	presi n - k alla volta, ossia:
**	P(n - k) = (n - k)! per un fissato k.
**
**	Infine, fissato un k con 0 <= k <= n, esistono C(n, k) modi per scegliere
**	quali k elementi stanno in A (C(n, k) modi per distribuire n elementi
**	tra A e B), senza considerare il loro ordine.
**	Per quel k, il numero di stati è:
**	C(n, k) * k! * (n - k)!
**	ma C(n, k) = n! / (k! * (n - k)!), quindi:
**	C(n, k) * k! * (n - k)! = n!
**
**	Cioè, per ogni possibile dimensione k di A (ossia per ogni singolo valore
**	fissato di k) ci sono n! stati.
**	Poiché k può assumere n + 1 valori, da 0 a n, lo spazio degli stati
**	è finito e contiene (n + 1) * n! stati.
**
**	Per n = 5:
**	(5 + 1) * 5! = 6 * 120 = 720 stati.
**
**	Si usa quindi un array statico di 720 nodi, sufficiente a contenere
**	l'intera BFS per SB_MAX = 5.
*/
# define SN_MAX 720

# define M_SA 1
# define M_SB 2
# define M_PB 3
# define M_PA 4
# define M_SS 5
# define M_RA 6
# define M_RB 7
# define M_RRA 8
# define M_RRB 9

typedef struct s_st
{
	int	a[SB_MAX];
	int	b[SB_MAX];
	int	a_size;
	int	b_size;
}	t_st;

typedef struct s_node
{
	t_st	state;
	int		prev;
	int		op;
}	t_node;

typedef struct s_bfs
{
	t_node	nodes[SN_MAX];
	int		visited[SN_MAX];
	int		idx;
	int		count;
	int		size;
	int		rest_a;
	int		rest_b;
}	t_bfs;

/* small_sort.c */
void	small_sort(t_ps *ps, int size, int from_b);

/* small_bfs_utils.c */
int		is_goal(t_st *state, int n);
void	apply_sort(t_ps *ps, t_node *nodes, int idx);
int		factorial(int n);
void	add_node(t_bfs *bfs, t_st *next, int op);

/* small_bfs_state.c */
int		state_code(t_st *state, int size);
void	adds_child_nodes(t_bfs *bfs);

/* small_bfs_apply_no_rotate.c */
int		try_apply_swap_op(t_st *dst, int op);
int		try_apply_push_op(t_st *dst, int op);

/* small_bfs_apply_rotate.c */
int		try_apply_rotate_op(t_st *dst, int op, t_bfs *bfs);

#endif
