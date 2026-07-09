/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_additions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 06:16:44 by aseveri           #+#    #+#             */
/*   Updated: 2026/07/07 10:13:58 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_ADDITIONS_H
# define SIMPLE_ADDITIONS_H

# include "pushswap.h"
# include "small_bfs_additions.h"

/* simple.c */
int			simple_sort(t_ps *ps, int block_size);

/* simple_push_to_b.c */
int			mark_lis(t_ps *ps, int n, int *keep);
void		push_non_lis_to_b(t_ps *ps, int n, int *keep);

/* simple_search_best_b.c */
int			best_pos_b(t_ps *ps);
int			insert_pos_a(t_ps *ps, int rank_b);
int			pos_min_a(t_ps *ps);

/* simple_push_to_a.c */
void		prepare_and_pa(t_ps *ps, int pos_b);

#endif
