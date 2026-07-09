/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peephole_optimizer_additions.h.                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:33:25 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:33:27 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PEEPHOLE_OPTIMIZER_ADDITIONS_H
# define PEEPHOLE_OPTIMIZER_ADDITIONS_H

# include "pushswap.h"

/* peephole_optimizer */
typedef struct s_pattern
{
	int	len;
	int	min_size_a;
	int	min_size_b;
	int	in[6];
	int	out_len;
	int	out[6];
}	t_pattern;

typedef struct s_peephole
{
	t_oplist	*ol;
	int			*ops_tmp;
	int			i;
	int			j;
	int			a_size;
	int			b_size;
}	t_peephole;

/* peephole_optimizer_core.c */
int		oplist_peephole_optimizer(t_oplist *ol, int initial_a_size);
int		try_table(t_peephole *tm, const t_pattern *patterns, int count);

/* peephole_optimizer_try_dispatcher.c */
int		try_any_pattern(t_peephole *tm);

/* peephole_optimizer_sizes.c */
void	peephole_optimizer_init(t_peephole *tm, t_oplist *ol,
			int *ops_tmp, int size);
void	peephole_optimizer_update_sizes_seq(t_peephole *tm, int start);
void	peephole_optimizer_copy_one(t_peephole *tm);
void	peephole_optimizer_copy_tmp_to_ops(t_oplist *ol,
			int *ops_tmp, int size);

/* peephole_optimizer_try_safe4.c */
int		try_safe5(t_peephole *tm);
int		try_safe4_a(t_peephole *tm);
int		try_safe4_b(t_peephole *tm);
int		try_safe4_c(t_peephole *tm);

/* peephole_optimizer_try_safe.c */
int		try_safe3_a(t_peephole *tm);
int		try_safe3_b(t_peephole *tm);
int		try_safe2(t_peephole *tm);

/* peephole_optimizer_try_cond6.c */
int		try_cond6(t_peephole *tm);

/* peephole_optimizer_try_cond5.c */
int		try_cond5_a(t_peephole *tm);
int		try_cond5_b(t_peephole *tm);
int		try_cond5_c(t_peephole *tm);
int		try_cond5_d(t_peephole *tm);
int		try_cond5_e(t_peephole *tm);

/* peephole_optimizer_try_cond.c */
int		try_cond4_a(t_peephole *tm);
int		try_cond4_b(t_peephole *tm);
int		try_cond4_c(t_peephole *tm);
int		try_cond3(t_peephole *tm);
int		try_cond2(t_peephole *tm);

/* peephole_optimizer_try_basic.c */
int		try_neutral_patterns(t_peephole *tm);
int		try_fusion_patterns(t_peephole *tm);

#endif
