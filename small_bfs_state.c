/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_bfs_state.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 06:16:44 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/17 06:16:48 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "small_bfs_additions.h"

/*
**	Ad ogni permutazione di n elementi distinti corrisponde uno ed un solo
**	vettore di Lehmer, e viceversa: ogni permutazione è in corrispondenza
**	biunivoca con un codice di Lehmer (ossia vi è una biiezione).
**
**	Il codice di Lehmer di una permutazione perm è il vettore L di n cifre
**	definito, per ogni indice i, come il numero di elementi a destra di i
**	(cioè con indice j > i, 0 <= i <= n - 1) che sono minori di perm[i]:
**
**	L[i] = card({ j : j > i, perm[j] < perm[i] }) con 0 <= i <= n - 1, i,n ∈ N^*
**
**	Per costruzione, ad ogni posizione i restano n - 1 - i elementi ancora
**	da confrontare (quelli alla sua destra), quindi ogni cifra L[i] è
**	necessariamente vincolata a rispettare:
**
**	0 <= L[i] <= n - 1 - i
**
**	Questo è esattamente l'insieme C definito qui sotto: l'insieme di tutti
**	e soli i vettori L che possono essere il codice di Lehmer di una
**	permutazione di n elementi.
**
**	C = { L | 0 <= L[i] <= n - 1 - i }
**
**	A sua volta, un vettore che rispetta questi vincoli sulle cifre è
**	esattamente un numero scritto in notazione factoradic (base mista
**	fattoriale), dove la cifra i-esima ha peso (n - 1 - i)!. La notazione
**	factoradic è anch'essa in corrispondenza biunivoca con gli interi
**	dell'intervallo [0, n! - 1] = [0, n!):
**	ogni intero in tale intervallo si scrive in uno ed un solo modo come
**	somma pesata delle cifre L[i] per (n - 1 - i)!.
**
**	Componendo le due biiezioni (permutazione <-> codice di Lehmer, e
**	codice di Lehmer <-> intero in notazione factoradic) si ottiene una
**	biiezione diretta:
**		permutazione di n elementi <-> intero in [0, n!)
**	che è esattamente ciò che questa funzione calcola:
**	dato un array perm che rappresenta una permutazione di n elementi,
**	restituisce l'unico intero in [0, n!) che la codifica.
*/
static int	perm_to_factoradic_code(int *perm, int n)
{
	int	factoradic_code;
	int	i;
	int	j;
	int	lehmer_digit_i;

	factoradic_code = 0;
	i = 0;
	while (i < n)
	{
		lehmer_digit_i = 0;
		j = i + 1;
		while (j < n)
		{
			if (perm[j] < perm[i])
				lehmer_digit_i++;
			j++;
		}
		factoradic_code += lehmer_digit_i * factorial(n - 1 - i);
		i++;
	}
	return (factoradic_code);
}

/*
**	Uno stato della BFS è individuato da una coppia ordinata di informazioni
**	indipendenti:
**	1) la dimensione a_size di A (a_size può assumere n + 1 valori distinti,
**	   da 0 a n <= SB_MAX, come mostrato in small_bfs_additions.h);
**	2) la permutazione ottenuta concatenando gli elementi di A (nell'ordine
**	   in cui compaiono in A) seguiti dagli elementi di B (nell'ordine in
**	   cui compaiono in B), corrispondente sempre ad una permutazione degli
**	   n elementi complessivi indipendentemente dalla loro distribuzione
**	   tra A e B.
**
**	   Per la biiezione dimostrata sopra, questa permutazione si codifica in
**	   uno ed un solo intero in [0, n!) tramite perm_to_factoradic_code.
**
**	Fissato a_size, tale intero identifica quindi in modo univoco lo stato
**	all'interno del blocco dei soli stati che condividono quella dimensione
**	di A.
**
**	Ne consegue che sommando a questo intero l'offset a_size * n!
**	(che trasla il codice nel blocco dipendente da a_size fra gli n + 1
**	blocchi disponibili, ciascuno di ampiezza n!) si ottiene un intero
**	che identifica lo stato in modo univoco tra tutti gli (n + 1) * n!
**	stati possibili:
**	è esattamente il codice usato come indice nell'array bfs->visited[SN_MAX].
**
**	Esempio numerico, se size = 5:
**
**	a_size = 0 -> code 0, ..., 119
**	a_size = 1 -> code 120, ..., 239
**	a_size = 2 -> code 240, ..., 359
**	a_size = 3 -> code 360, ..., 479
**	a_size = 4 -> code 480, ..., 599
**	a_size = 5 -> code 600, ..., 719
**
**	Poiché state_code è calcolato con un numero costante di operazioni
**	aritmetiche, indipendente dal numero di stati già visitati, il
**	controllo "questo stato è già stato visitato?" (in seen_state_fast) si
**	riduce ad un singolo accesso diretto in bfs->visited[code]: un costo
**	O(1), al posto della scansione lineare su tutti i nodi già trovati
**	(costo O(k), con k pari al numero di stati visitati finora) usata in una
**	precedente implementazione.
*/
int	state_code(t_st *state, int size)
{
	int	perm[SB_MAX];
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (i < state->a_size)
		perm[k++] = state->a[i++];
	i = 0;
	while (i < state->b_size)
		perm[k++] = state->b[i++];
	return (state->a_size * factorial(size) + perm_to_factoradic_code(perm,
			size));
}

static int	seen_state_fast(t_bfs *bfs, t_st *state)
{
	int	code;

	code = state_code(state, bfs->size);
	if (bfs->visited[code])
		return (1);
	bfs->visited[code] = 1;
	return (0);
}

static int	try_apply_op(t_st *next_state, t_st state, int op, t_bfs *bfs)
{
	*next_state = state;
	if (try_apply_swap_op(next_state, op))
		return (1);
	if (try_apply_push_op(next_state, op))
		return (1);
	if (try_apply_rotate_op(next_state, op, bfs))
		return (1);
	return (0);
}

void	adds_child_nodes(t_bfs *bfs)
{
	t_st	next_state;
	int		op;

	op = M_SA;
	while (op <= M_RRB)
	{
		if (bfs->count < SN_MAX
			&& try_apply_op(&next_state, bfs->nodes[bfs->idx].state, op, bfs)
			&& !seen_state_fast(bfs, &next_state))
			add_node(bfs, &next_state, op);
		op++;
	}
}
