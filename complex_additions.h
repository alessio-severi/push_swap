/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_additions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:33:42 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:33:43 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_ADDITIONS_H
# define COMPLEX_ADDITIONS_H

# include "pushswap.h"
# include "small_bfs_additions.h"

typedef struct s_key
{
	int	mult;
	int	offset;
	int	initial_encoded_flag;
}	t_key;

typedef struct s_recode
{
	int		*data;
	int		block_size;
	int		expensive_trit;
	int		*pow3;
}	t_recode;

/* complex.c */
void	complex_sort(t_ps *ps, int n);

void	complex_sort_a_top(t_ps *ps, int block_size, int pow3, t_key key);
void	complex_sort_b_top(t_ps *ps, int block_size, int pow3, t_key key);
void	complex_sort_a_bottom(t_ps *ps, int block_size, int pow3, t_key key);
void	complex_sort_b_bottom(t_ps *ps, int block_size, int pow3, t_key key);

/* complex_sort_core.c */
void	complex_sort_a_top_core(t_ps *ps, int block_size, int pow3,
			int *count);
void	complex_sort_a_bottom_core(t_ps *ps, int block_size, int pow3,
			int *count);
void	complex_sort_b_top_core(t_ps *ps, int block_size, int pow3,
			int *count);
void	complex_sort_b_bottom_core(t_ps *ps, int block_size, int pow3,
			int *count);

/* complex_encoded_rank.c */
t_key	encoded_key(int n);

/* complex_recode_dispatcher.c */
t_key	recode_a_top(t_ps *ps, int block_size, t_key old_key, int *pow3);
t_key	recode_a_bottom(t_ps *ps, int block_size, t_key old_key, int *pow3);
t_key	recode_b_top(t_ps *ps, int block_size, t_key old_key, int *pow3);
t_key	recode_b_bottom(t_ps *ps, int block_size, t_key old_key, int *pow3);

/* complex_recode.c */
t_key	recode_block(t_recode *rc, t_key old_key);

/* complex_decode.c. */
int		decode_rank(int value, t_key key);
int		min_decode_rank(t_recode *rc, t_key old_key);

/* complex_utils.c */
int		max_rank_pow3(int n);
int		next_pow3(int pow3);
int		trit_value(int value, int pow3);
void	init_counts(int *count);
int		max_encoded_rank_pow3(int n, t_key key);

/* complex_lift_bottom.c */
void	lift_a_bottom(t_ps *ps, int block_size);
void	lift_b_bottom(t_ps *ps, int block_size);
void	pa_n(t_ps *ps, int block_size);

/* complex_check_block_sorted.c */
int		is_sorted_a_top(t_ps *ps, int block_size);
int		is_rev_sorted_b_top(t_ps *ps, int block_size);
int		is_sorted_a_bottom(t_ps *ps, int block_size);
int		is_rev_sorted_b_bottom(t_ps *ps, int block_size);

#endif
