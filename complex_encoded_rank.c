/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_encoded_rank.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 08:32:47 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/28 08:32:49 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex_additions.h"

/*
**	L'algoritmo qui esposto è un radix dinamico in base 3 ricorsivo con
**	suddivisione dei due stack in top e bottom ciascuno, con codifica e
**	ricodifica del rank, una volta ripristinato il rank originario per
**	quest'ultimo caso, all'inizio di ogni chiamata ricorsiva. Al fine di
**	ottimizzare il numero di mosse eseguite da push swap, mantenendo la
**	complessità algoritmica come da specifiche.
**
**	In particolare, sebbene l'algoritmo radix si basa su una processazione
**	dei dati, i rank, prevedibile e statica dal punto vista algoritmico,
**	in questo caso i dati vengono manipolati tramite codifica affinché
**	l'operato stesso del radix diventi modulato, pilotato, verso una
**	curva di lavoro dinamicamente più efficiente per l'obiettivo di
**	push swap: ordinare una sequenza numerica in ingresso con un numero di
**	mosse che fosse il più basso possibile rispettando le specifiche imposte.
**
**	La codifica, quindi, segue alla base un modello teorico qui formulato
**	che ha come obiettivo, ad ogni chiamata ricorsiva, far sì che il trit più
**	alto produca 3 bucket bilanciati in termini di size: in un rank puro, esso
**	spesso non arriva abbastanza in alto nella finestra ternaria e
**	quindi il bucket 2 può essere vuoto o debole, sbilanciato rispetto
**	agli altri o degenerare in una suddivisione binaria, conseguentemente
**	più in generale, aumentare globalmente il numero di chiamate ricorsive
**	e quindi il numero di mosse necessarie per l'ordinamento.
**
**	Quindi si è scelto di codificare ogni rank tramite una
**	trasformazione affine:
**
**	encoded_rank = mult * rank + offset
**
**	successivamente per il calcolo di mult si è deciso di approssimare
**	encoded_rank = mult * rank
**	quindi calcolare il limite superiore ideale affinché il lavoro di split
**	rispetto al trit più alto produca 3 bucket bilanciati, ossia al
**	valore precedente alla potenza in base 3 successiva alla potenza
**	in base 3 più alta contenuta nel valore massimo del rank non codificato:
**
**	limit₀ = max_rank_pow3(n) * 3 =>
**	limit₀ - 1 = max_encoded_rank = mult₀ * max_rank = mult₀ * (n - 1) =>
**	mult₀ = (limit₀ - 1) / (n - 1)
**
**	Infine per quanto riguarda la seconda componente della trasformazione
**	affine, l'offset, si è scelto intenzionalmente:
**
**	mult = floor((limit - 1) / (n - 1)),
**	in modo tale che offset_max = (limit - 1) - ((n - 1) * mult)
**
**	e dunque la fascia di ricerca dell'offset risulti finita e ben definita:
**
**	0 <= offset <= offset_max
**
**	Tra tutti gli offset che realizzano lo stesso bilanciamento ottimo
**	(stesso split_score minimo), tuttavia, non si è scelto un criterio
**	analitico che permetta di scegliere a priori quale, tra questi, sia
**	realmente il migliore in termini di mosse totali risparmiate:
**	split_score misura infatti solo lo sbilanciamento tra i bucket, non
**	il costo effettivo dell'ordinamento.
**
**	Dunque si è inoltre imposto che qualunque offset venga scelto tra quelli a
**	pari merito, il suo impatto sul risultato finale resti comunque limitato
**	per costruzione.
**	Quindi si è minimizzato il ruolo dell'offset moltiplicando limit₀
**	per un fattore pari alla prima potenza di 3 extra_depth volte,
**	ossia
**
**	limit = limit₀ * 3^extra_depth, con extra_depth = 2
**
**	All'interno di questa fascia di offset, l'offset specifico viene infine
**	scelto per ricerca esaustiva (vedi best_offset_for_mult).
**
**	A conclusione, i risultati ottenuti dopo vari test pre e post refactoring
**	codificando i rank sono:
**	per esempio per n = 500 una riduzione di più di 300 mosse solo applicando
**	una codifica globale alla prima ricorsione, mentre se si applica una
**	ricodifica prima ogni ricorsione successiva alla prima, con codifica
**	personalizzata prima degli ultimi blocchi in modo da ottimizzare il
**	lavoro della bfs, come descritto in complex_recode.c, la riduzione
**	sale a circa 450 mosse.
*/
static int	encoded_limit(int n, int extra_depth)
{
	int	limit;

	limit = max_rank_pow3(n) * 3;
	while (extra_depth-- > 0)
		limit *= 3;
	return (limit);
}

static int	encoded_mult(int n, int extra_depth)
{
	int	limit;

	limit = encoded_limit(n, extra_depth);
	return ((limit - 1) / (n - 1));
}

static int	split_score(int n, int mult, int offset)
{
	int	count[3];
	int	pow3;
	int	i;
	int	max;
	int	min;

	count[0] = 0;
	count[1] = 0;
	count[2] = 0;
	pow3 = max_rank_pow3((n - 1) * mult + offset + 1);
	i = -1;
	while (++i < n)
		count[((i * mult + offset) / pow3) % 3]++;
	max = count[0];
	if (count[1] > max)
		max = count[1];
	if (count[2] > max)
		max = count[2];
	min = count[0];
	if (count[1] < min)
		min = count[1];
	if (count[2] < min)
		min = count[2];
	return (max - min);
}

static int	best_offset_for_mult(int n, int mult, int limit)
{
	int	offset;
	int	offset_max;
	int	best_offset;
	int	best_score;
	int	score;

	offset_max = (limit - 1) - ((n - 1) * mult);
	offset = 0;
	best_score = split_score(n, mult, offset);
	best_offset = offset;
	while (++offset <= offset_max)
	{
		score = split_score(n, mult, offset);
		if (score <= best_score)
		{
			best_score = score;
			best_offset = offset;
		}
	}
	return (best_offset);
}

t_key	encoded_key(int n)
{
	t_key	key;
	int		extra_depth;
	int		limit;

	extra_depth = 2;
	limit = encoded_limit(n, extra_depth);
	key.mult = encoded_mult(n, extra_depth);
	key.offset = best_offset_for_mult(n, key.mult, limit);
	key.initial_encoded_flag = 1;
	return (key);
}
